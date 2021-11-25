#include "pressureSolver.hpp"

#include <tuple>

#include "calc/models/diagMatrix.hpp"
#include "calc/services/workSigma.hpp"
#include "common/models/commonVals.hpp"

namespace ble::src::calc::services {

double get_h(const std::shared_ptr<mm::Face> fc, const std::shared_ptr<mm::Grid> grd,
    const std::shared_ptr<common::models::InputData> data)
{
    auto regular = [&]() {
        return (fc->cl2 == -1)
            ? std::abs(grd->cells[fc->cl1]->cntr - fc->x)
            : std::abs(grd->cells[fc->cl1]->cntr - grd->cells[fc->cl2]->cntr);
    };

    // auto correct_radial = [&](double r, double rw) {
    //     double a = (r - 1.0) * (r + 1.0) * (r + 1.0) * (r - rw) * (r + rw);
    //     double a2 = 2.0 * r * (r - rw) * (r + rw) * std::log(rw);
    //     double a3 = 2.0 * r * r * r * (rw * rw - 1.0) * std::log(rw / r);
    //     double b1 = a / (a2 + a3);
    //     return b1;
    // };

    auto correct_radial2 = [&](double d, double rw) {
        double a = 16.0 * (d * d - 4.0 * rw * rw);
        double a2 = -9.0 * (d * d - 4.0 * rw * rw) * std::log(2.0 * rw / 3.0 / d);
        double a3 = (9.0 * d * d - 4.0 * rw * rw) * std::log(2.0 * rw / d);
        double b1 = a / (a2 + a3);
        return b1;
    };

    if (fc->type == mm::FaceType::kWell) {
        switch (data->grd->type) {
        case common::models::GridType::kRadial: {
            double rw = data->grd->rw;
            double d = grd->cells[fc->cl1]->cntr;
            double b2 = regular();
            double b3 = correct_radial2(d, rw);
            return b2 / b3;
        }
        default:
            return regular();
        }
    }

    return regular();
}

std::vector<double> solve_press(const std::shared_ptr<mm::Grid> grd, const std::vector<double>& s,
    const std::shared_ptr<common::models::InputData> data)
{
    models::DiagMat ret;
    ret.resize(grd->cells.size());

    std::vector<double> rhs(grd->cells.size(), 0.0);

    for (auto& fc : grd->faces) {
        double sigma = get_face_sigma(fc, s, data->data->phys, grd);
        double h = get_h(fc, grd, data);
        double cf = fc->area * sigma / h;

        switch (fc->type) {
        case mm::FaceType::kInner: {
            ret.C[fc->cl1] += cf;
            ret.A[fc->cl1] -= cf;
            ret.B[fc->cl2] -= cf;
            ret.C[fc->cl2] += cf;
            break;
        }
        case mm::FaceType::kWell:
        case mm::FaceType::kContour: {
            if (!common::models::CommonVals::is_empty(fc->bound_press)) {
                rhs[fc->cl1] += cf * fc->bound_press;
                ret.C[fc->cl1] += cf;
            }
            break;
        }
        case mm::FaceType::kTop:
        case mm::FaceType::kBot: {
            rhs[fc->cl1] += fc->area * fc->bound_u;
            break;
        }
        default:
            break;
        }
    }

    return ret.solve(rhs);
}

void calc_u(const std::vector<double>& p, const std::vector<double>& s,
    const std::shared_ptr<common::models::InputData> data, std::shared_ptr<mm::Grid> grd)
{
    for (auto& fc : grd->faces) {

        if (mm::FaceType::is_top_bot(fc->type)) {
            fc->u = fc->bound_u;
            continue;
        }

        if (mm::FaceType::is_well_countour(fc->type) && common::models::CommonVals::is_empty(fc->bound_press)) {
            fc->u = 0.0; // empty bound press means that face is impermeable;
            continue;
        }

        double sigma = get_face_sigma(fc, s, data->data->phys, grd);
        double h = get_h(fc, grd, data);

        double p1 = p[fc->cl1];
        double p2 = mm::FaceType::is_well_countour(fc->type)
            ? fc->bound_press
            : p[fc->cl2];

        fc->u = -sigma * (p1 - p2) / h;
    }
}

std::vector<double> calc_press_exact(const std::shared_ptr<mm::Grid> grd,
    const std::shared_ptr<common::models::InputData> data)
{
    std::vector<double> result;
    double pw = 0.0, pc = 1.0;
    double rw = data->grd->rw, rc = data->grd->rc;

    auto calc_p_aver_radial = [&](const std::shared_ptr<mm::Cell> cl) {
        auto m = [](double r) { return (r * r / 2.0) * (std::log(r) - 0.5); };

        double alp = (pc - pw) / std::log(rc / rw);
        double v = cl->volume;
        double gam = pw - alp * std::log(rw);
        double d = alp * 2.0 * M_PI / v;
        return gam + d * (m(cl->xr) - m(cl->xl));
    };

    auto calc_p_regular = [&](double x) {
        double a = (pc - pw) / (rc - rw);
        double b = (rc * pw - rw * pc) / (rc - rw);
        return a * x + b;
    };

    for (auto& cl : grd->cells) {
        double p = 0.0;
        switch (data->grd->type) {
        case common::models::GridType::kRadial:
            p = calc_p_aver_radial(cl);
            break;
        case common::models::GridType::kRegular:
            p = calc_p_regular(cl->cntr);
            break;
        default:
            p = 1.0;
            break;
        }
        result.push_back(p);
    }

    return result;
}

}

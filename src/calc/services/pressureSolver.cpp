#include "pressureSolver.hpp"

#include <tuple>

#include "calc/models/diagMatrix.hpp"
#include "calc/services/workSigma.hpp"

namespace ble::src::calc::services {

double get_h(const std::shared_ptr<mm::Face> fc, const std::shared_ptr<mm::Grid> grd,
    const std::shared_ptr<common::models::InputData> data)
{
    auto regular = [&]() {
        return (fc->cl2 == -1)
            ? std::abs(grd->cells[fc->cl1]->cntr - fc->x)
            : std::abs(grd->cells[fc->cl1]->cntr - grd->cells[fc->cl2]->cntr);
    };

    if (fc->type == mm::FaceType::kWell) {
        switch (data->grd->type) {
        case common::models::GridType::kRadial:
            return regular(); // log(data->grd->rc / data->grd->rw) * data->grd->rw;
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
        double sigma = get_face_sigma(fc, s, data->phys, grd);
        double h = get_h(fc, grd, data);
        double cf = fc->area * sigma / h;

        if (fc->type != mm::FaceType::kInner) {
            rhs[fc->cl1] += cf * fc->bound_press;
            ret.C[fc->cl1] += cf;
        } else {
            ret.C[fc->cl1] += cf;
            ret.A[fc->cl1] -= cf;
            ret.B[fc->cl2] -= cf;
            ret.C[fc->cl2] += cf;
        }
    }

    return ret.solve(rhs);
}

void calc_u(const std::vector<double>& p, const std::vector<double>& s,
    const std::shared_ptr<common::models::InputData> data, std::shared_ptr<mm::Grid> grd)
{
    for (auto& fc : grd->faces) {
        double sigma = get_face_sigma(fc, s, data->phys, grd);
        double h = get_h(fc, grd, data);

        double p1 = p[fc->cl1];
        double p2 = (fc->cl2 == -1)
            ? fc->bound_press
            : p[fc->cl2];

        fc->u = -sigma * (p1 - p2) / h;
    }
}

}

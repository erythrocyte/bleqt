#include "makeGrid.hpp"

#include <math.h>

#include "common/models/commonVals.hpp"
#include "common/services/dataDistributionService.hpp"
#include "common/services/workString.hpp"
#include "logging/logger.hpp"

namespace ble::src::mesh::services {

std::shared_ptr<mesh::models::Face> make_face(int ind, double x, int cl1, int cl2, double area,
    mesh::models::FaceType::TypeEnum face_type, double bound_p, double bound_s, double bound_u)
{
    auto fc = std::make_shared<mesh::models::Face>();
    fc->ind = ind;
    fc->cntr = x;
    fc->cl1 = cl1;
    fc->cl2 = cl2;
    fc->area = area;
    fc->type = face_type;
    fc->bound_press = bound_p;
    fc->bound_satur = bound_s;
    fc->bound_u = bound_u;

    return fc;
};

void check_cells_volume(const std::shared_ptr<common::models::SolverData> params,
    const std::shared_ptr<mesh::models::Grid> grd)
{
    auto get_analytic_volume = [&]() {
        double rc = 1.0, rw = params->rw;
        switch (params->mesh_setts->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return rc;
        case common::models::GridType::TypeEnum::kRadial: {
            return M_PI * (rc * rc - rw * rw);
        }
        default:
            return 0.0;
        }
    };

    auto get_numeric_volume = [&]() {
        double result = 0.0;
        for (auto& cl : grd->cells)
            result += cl->volume;

        return result;
    };

    auto get_caption = [&]() {
        switch (params->mesh_setts->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return "regular";
        case common::models::GridType::TypeEnum::kRadial:
            return "radial";
        default:
            return "";
        }
    };

    double anvol = get_analytic_volume();
    double numvol = get_numeric_volume();
    std::string cap = get_caption();

    std::string mess = common::services::string_format("for %s grid analytical volume is %.6f, numeric volume is %.6f.", cap, anvol, numvol);
    logging::write_log(mess, logging::kDebug);
}

std::shared_ptr<mesh::models::Grid> make_grid(const std::shared_ptr<common::models::SolverData> params)
{
    auto get_x = [&](double step, int k) {
        switch (params->mesh_setts->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return step * k;
        case common::models::GridType::TypeEnum::kRadial:
            return params->rw + step * k;
        default:
            return 0.0;
        }
    };

    auto get_cyl_area = [&](double x) {
        switch (params->mesh_setts->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return 1.0;
        case common::models::GridType::TypeEnum::kRadial:
            return 2.0 * M_PI * x;
        default:
            return 0.0;
        }
    };

    auto get_x_bound = [&](int k, double step) {
        switch (params->mesh_setts->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return k * step;
        case common::models::GridType::TypeEnum::kRadial:
            return params->rw + k * step;
        default:
            return 0.0;
        }
    };

    auto get_cell_volume = [&](double step, double xl, double xr) {
        switch (params->mesh_setts->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return step;
        case common::models::GridType::TypeEnum::kRadial:
            return M_PI * (xr * xr - xl * xl); // Pi (r1^2 - r0^2);
        default:
            return 0.0;
        }
    };

    std::shared_ptr<mesh::models::Grid> result(new mesh::models::Grid());
    double empty_val = common::models::CommonVals::EMPTY_VAL;
    double step = params->get_lenght() / params->mesh_setts->n;

    for (int k = 0; k < params->mesh_setts->n; k++) { // cells
        auto tp = (k == 0)
            ? mesh::models::FaceType::kWell
            : mesh::models::FaceType::kInner;
        double x = get_x(step, k);
        double area = get_cyl_area(x);
        auto fc = make_face(k, x, k, k - 1, area, tp, 0.0, empty_val, empty_val);
        result->faces.push_back(fc);

        std::shared_ptr<mesh::models::Cell> cl(new mesh::models::Cell());
        cl->ind = k;
        cl->xl = get_x_bound(k, step);
        cl->xr = get_x_bound(k + 1, step);
        cl->cntr = (cl->xr + cl->xl) / 2.0;
        cl->faces.push_back(k);
        cl->faces.push_back(k + 1);
        cl->volume = get_cell_volume(step, cl->xl, cl->xr);
        cl->poro = 1.0;
        cl->perm = params->perm_fract;
        result->cells.push_back(cl);
    }

    bool isolated_contour = params->contour_press_bound_type == common::models::BoundCondType::kImpermeable;
    double contour_bound_press = isolated_contour
        ? common::models::CommonVals::EMPTY_VAL
        : 1.0;

    // last face;
    auto fc = make_face(params->mesh_setts->n, 1.0, params->mesh_setts->n - 1, -1,
        get_cyl_area(1.0), mesh::models::FaceType::kContour,
        contour_bound_press, params->bound_satur, 0.0);
    result->faces.push_back(fc);

    // up and bottom faces;
    size_t ind = result->faces.size();
    for (auto& cl : result->cells) {
        double area = get_cell_volume(step, cl->xl, cl->xr);
        double bound_u = common::models::CommonVals::EMPTY_VAL;
        double bound_s = isolated_contour
            ? common::services::DataDistributionService::get_value(cl->cntr, params->top_bot_bound_s, 0.0)
            : 0.0;
        auto top = make_face(ind++, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kTop,
            common::models::CommonVals::EMPTY_VAL, bound_s, bound_u);
        result->faces.push_back(top);

        auto bot = make_face(ind++, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kBot,
            common::models::CommonVals::EMPTY_VAL, bound_s, bound_u);
        result->faces.push_back(bot);
    }

    // check_cells_volume(params, result);

    // calc sum volume
    for(auto &cl: result->cells) {
        result->sum_volume += cl->volume;
    }

    return result;
}
}

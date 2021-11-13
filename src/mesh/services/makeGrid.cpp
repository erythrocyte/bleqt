#include "makeGrid.hpp"

#include <math.h>

#include "common/models/commonVals.hpp"
#include "common/services/dataDistributionService.hpp"

namespace ble::src::mesh::services {

std::shared_ptr<mesh::models::Face> make_face(int ind, double x, int cl1, int cl2, double area,
    mesh::models::FaceType::TypeEnum face_type, double bound_p, double bound_s, double bound_u)
{
    auto fc = std::make_shared<mesh::models::Face>();
    fc->ind = ind;
    fc->x = x;
    fc->cl1 = cl1;
    fc->cl2 = cl2;
    fc->area = area;
    fc->type = face_type;
    fc->bound_press = bound_p;
    fc->bound_satur = bound_s;
    fc->bound_u = bound_u;

    return fc;
};

std::shared_ptr<mesh::models::Grid> make_grid(const std::shared_ptr<common::models::InputData> data)
{
    auto get_x = [&](double step, int k) {
        switch (data->grd->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return step * k;
        case common::models::GridType::TypeEnum::kRadial:
            return data->grd->rw + step * k;
        default:
            return 0.0;
        }
    };

    auto get_cyl_area = [&](double x) {
        switch (data->grd->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return 1.0;
        case common::models::GridType::TypeEnum::kRadial:
            return 2.0 * M_PI * x;
        default:
            return 0.0;
        }
    };

    auto get_x_bound = [&](int k, double step) {
        switch (data->grd->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return k * step;
        case common::models::GridType::TypeEnum::kRadial:
            return data->grd->rw + k * step;
        default:
            return 0.0;
        }
    };

    auto get_cell_volume = [&](double step, double xl, double xr) {
        switch (data->grd->type) {
        case common::models::GridType::TypeEnum::kRegular:
            return step;
        case common::models::GridType::TypeEnum::kRadial:
            return M_PI * (xr * xr - xl * xl); // Pi (r1^2 - r0^2);
        default:
            return 0.0;
        }
    };

    std::shared_ptr<mesh::models::Grid> result(new mesh::models::Grid());
    double step = data->grd->get_lenght() / data->grd->n;

    for (int k = 0; k < data->grd->n; k++) { // cells
        auto tp = (k == 0)
            ? mesh::models::FaceType::kWell
            : mesh::models::FaceType::kInner;
        double x = get_x(step, k);
        double area = get_cyl_area(x);
        auto fc = make_face(k, x, k, k - 1, area, tp, 0.0, 0.0, 0.0);
        result->faces.push_back(fc);

        std::shared_ptr<mesh::models::Cell> cl(new mesh::models::Cell());
        cl->ind = k;
        cl->xl = get_x_bound(k, step);
        cl->xr = get_x_bound(k + 1, step);
        cl->cntr = (cl->xr + cl->xl) / 2.0;
        cl->faces.push_back(k);
        cl->faces.push_back(k + 1);
        cl->volume = get_cell_volume(step, cl->xl, cl->xr);
        cl->poro = data->phys->poro;
        cl->perm = data->phys->perm;
        result->cells.push_back(cl);
    }

    bool isolated_contour = data->bound->contour_press_bound_type == common::models::BoundCondType::kImpermeable;
    double contour_bound_press = isolated_contour
        ? common::models::CommonVals::EMPTY_VAL
        : 1.0;

    // last face;
    auto fc = make_face(data->grd->n, data->grd->rc, data->grd->n - 1, -1,
        get_cyl_area(data->grd->rc), mesh::models::FaceType::kContour,
        contour_bound_press, data->bound->bound_satur, 0.0);
    result->faces.push_back(fc);

    // up and bottom faces;
    size_t ind = result->faces.size();
    for (auto& cl : result->cells) {
        double area = get_cell_volume(step, cl->xl, cl->xr);
        double bound_u = common::services::DataDistributionService::get_value(cl->cntr, data->bound->top_bot_bound_u, 0.0);
        auto top = make_face(ind, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kTop, common::models::CommonVals::EMPTY_VAL, 1.0, bound_u);
        ind++;
        result->faces.push_back(top);

        auto bot = make_face(ind, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kBot, common::models::CommonVals::EMPTY_VAL, 1.0, bound_u);
        ind++;
        result->faces.push_back(bot);
    }

    return result;
}

}

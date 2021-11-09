#include "makeGrid.hpp"

#include <math.h>

namespace ble::src::mesh::services {

std::shared_ptr<mesh::models::Face> make_face(int ind, double x, int cl1, int cl2, double area,
    mesh::models::FaceType::TypeEnum face_type, double bound_p, double bound_s, double bound_u, bool isolated)
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
    fc->isolated = isolated;

    return fc;
};

std::shared_ptr<mesh::models::Grid> make_regular_grid(const std::shared_ptr<common::models::InputData> data)
{
    std::shared_ptr<mesh::models::Grid> result(new mesh::models::Grid());
    double step = data->grd->get_lenght() / data->grd->n;

    for (int k = 0; k < data->grd->n; k++) { // cells
        auto tp = (k == 0)
            ? mesh::models::FaceType::kWell
            : mesh::models::FaceType::kInner;
        auto fc = make_face(k, step * k, k, k - 1, 1.0, tp, 0.0, 0.0, 0.0, false);
        result->faces.push_back(fc);

        std::shared_ptr<mesh::models::Cell> cl(new mesh::models::Cell());
        cl->ind = k;
        cl->xl = k * step;
        cl->xr = (k + 1) * step;
        cl->cntr = (cl->xr + cl->xl) / 2.0;
        cl->faces.push_back(k);
        cl->faces.push_back(k + 1);
        cl->volume = step;
        cl->poro = data->phys->poro;
        cl->perm = data->phys->perm;
        result->cells.push_back(cl);
    }

    // bool isolated_top_bot = data->bound->bound_type == common::models::BoundCondType::kConst;

    // last face;    
    auto fc = make_face(data->grd->n, data->grd->rc, data->grd->n - 1, -1,
        1.0, mesh::models::FaceType::kContour, 1.0, 1.0, 0.0, !isolated_top_bot);
    result->faces.push_back(fc);

    // up and bottom faces;
    size_t ind = result->faces.size();
    for (auto& cl : result->cells) {
        double area = cl->xr - cl->xl;
        double bound_u = data->bound->get_value(cl->cntr);
        auto top = make_face(ind, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kTop, 0.0, 1.0, bound_u, isolated_top_bot);
        ind++;
        result->faces.push_back(top);

        auto bot = make_face(ind, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kBot, 0.0, 1.0, bound_u, isolated_top_bot);
        ind++;
        result->faces.push_back(bot);
    }

    return result;
}

std::shared_ptr<mesh::models::Grid> make_radial_grid(const std::shared_ptr<common::models::InputData> data)
{
    std::shared_ptr<mesh::models::Grid> result(new mesh::models::Grid());
    double step = data->grd->get_lenght() / data->grd->n;

    for (int k = 0; k < data->grd->n; k++) { // cells
        auto tp = (k == 0)
            ? mesh::models::FaceType::kWell
            : mesh::models::FaceType::kInner;
        double x = data->grd->rw + step * k;
        auto fc = make_face(k, x, k, k - 1, 2.0 * M_PI * x, tp, 0.0, 0.0, 0.0, false);
        result->faces.push_back(fc);

        std::shared_ptr<mesh::models::Cell> cl(new mesh::models::Cell());
        cl->ind = k;
        cl->xl = data->grd->rw + k * step;
        cl->xr = data->grd->rw + (k + 1) * step;
        cl->cntr = (cl->xr + cl->xl) / 2.0;
        cl->faces.push_back(k);
        cl->faces.push_back(k + 1);
        cl->volume = M_PI * (cl->xr * cl->xr - cl->xl * cl->xl); // Pi (r1^2 - r0^2);
        cl->poro = data->phys->poro;
        cl->perm = data->phys->perm;
        result->cells.push_back(cl);
    }

    bool isolated_top_bot = data->bound->bound_type == common::models::BoundCondType::kConst;

    // last face;
    double x = data->grd->rc;
    auto fc = make_face(data->grd->n, x, data->grd->n - 1, -1, 2.0 * M_PI * x,
        mesh::models::FaceType::kContour, 1.0, 1.0, 0.0, !isolated_top_bot);
    result->faces.push_back(fc);

    // up and bottom faces;
    size_t ind = result->faces.size();
    for (auto& cl : result->cells) {
        double area = M_PI * (cl->xr * cl->xr - cl->xl * cl->xl);
        double bound_u = isolated_top_bot ? 0.0 : data->bound->get_value(cl->cntr);
        auto top = make_face(ind, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kTop, 0.0, 1.0, bound_u, isolated_top_bot);
        ind++;
        result->faces.push_back(top);

        auto bot = make_face(ind, cl->cntr, cl->ind, -1, area, mesh::models::FaceType::kBot, 0.0, 1.0, bound_u, isolated_top_bot);
        ind++;
        result->faces.push_back(bot);
    }

    // double rc = data->grd->rc, rw = data->grd->rw;
    // double an_area = M_PI * (rc * rc - rw * rw);
    // double num_area = 0.0;
    // for (auto &cl: result->cells) {
    //     num_area += cl->volume;
    // }

    return result;
}

std::shared_ptr<mesh::models::Grid> make_grid(const std::shared_ptr<common::models::InputData> data)
{
    switch (data->grd->type) {
    case common::models::GridType::TypeEnum::kRegular:
        return make_regular_grid(data);
    case common::models::GridType::TypeEnum::kRadial:
        return make_radial_grid(data);
    // case common::models::GridType::TypeEnum::kSpheric:
    default:
        return std::make_shared<mesh::models::Grid>();
    }
}

}

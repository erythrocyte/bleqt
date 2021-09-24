#include "makeGrid.hpp"

namespace ble::src::mesh::services {

std::shared_ptr<mesh::models::Grid> make_regular_grid(const std::shared_ptr<common::models::InputData> data)
{
    std::shared_ptr<mesh::models::Grid> result(new mesh::models::Grid());
    double step = data->grd->l / data->grd->n;

    for (int k = 0; k < data->grd->n; k++) { // cells
        std::shared_ptr<mesh::models::Face> fc(new mesh::models::Face());
        fc->ind = k;
        fc->x = step * k;
        fc->cl1 = k;
        fc->cl2 = k - 1;
        fc->type = (k == 0)
            ? mesh::models::FaceType::kWell
            : mesh::models::FaceType::kInner;
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

    // last face;
    std::shared_ptr<mesh::models::Face> fc(new mesh::models::Face());
    fc->ind = data->grd->n;
    fc->x = data->grd->l;
    fc->cl1 = data->grd->n - 1;
    fc->type = mesh::models::FaceType::kContour;
    fc->bound_press = 1.;
    fc->bound_satur = 1.;
    result->faces.push_back(fc);

    return result;
}

std::shared_ptr<mesh::models::Grid> make_grid(const std::shared_ptr<common::models::InputData> data)
{
    switch (data->grd->type) {
    case common::models::GridType::TypeEnum::kRegular:
        return make_regular_grid(data);
    case common::models::GridType::TypeEnum::kRadial:
    case common::models::GridType::TypeEnum::kSpheric:
    default:
        return std::make_shared<mesh::models::Grid>();
    }
}

}

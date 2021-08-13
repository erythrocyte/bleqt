#include "saturSolverNum.hpp"

#include "common/services/workRp.hpp"

namespace cs = ble_src::common::services;

namespace ble_src::calc::services {

std::vector<double> solve_explicit(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::InputData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    std::vector<double> result(init.size(), 0.);

    std::vector<double> dvs(grd->cells.size(), 0.);

    for (auto& fc : grd->faces) {
        double s = (fc->u > 0.)
            ? (fc->cl2 == -1)
                ? fc->bound_satur
                : init[fc->cl2]
            : init[fc->cl1];

        double fbl = cs::rp::get_fbl(s, data->phys);
        double cf = fc->u * fbl * fc->area;
        dvs[fc->cl1] += cf;
        if (fc->cl2 != -1)
            dvs[fc->cl2] -= cf;
    }

    for (auto& cl : grd->cells) {
        result[cl->ind] = init[cl->ind] + tau / (data->phys->poro * cl->volume) * dvs[cl->ind];
    }

    return result;
}

std::vector<double> solve_satur(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::InputData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    switch (data->satSetts->type) {
    case calc::models::SaturSolverType::TypeEnum::kExplicit:
        return solve_explicit(tau, init, data, grd);
    case calc::models::SaturSolverType::TypeEnum::kImplicit:
    default:
        return solve_explicit(tau, init, data, grd);
    }
}

}

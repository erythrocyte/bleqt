#include "saturSolverNum.hpp"

#include "common/services/workRp.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

std::vector<double> solve_explicit(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    // auto get_u = [&](const std::shared_ptr<mesh::models::Face> fc) {
    //     switch (fc->type) {
    //     case mesh::models::FaceType::kBot:
    //     case mesh::models::FaceType::kTop:
    //         return fc->bound_u;
    //     default:
    //         return fc->u;
    //     }
    // };
    auto get_s = [&](const std::shared_ptr<mesh::models::Face> fc, double u) {
        return (u > 0.)
            ? (fc->cl2 == -1)
                ? fc->bound_satur
                : init[fc->cl2]
            : init[fc->cl1];
    };

    std::vector<double> result(init.size(), 0.);
    std::vector<double> dvs(grd->cells.size(), 0.);

    for (auto& fc : grd->faces) {
        double u = fc->u; // get_u(fc);
        double s = get_s(fc, u);
        double fbl = cs::rp::get_fbl(s, data->rp_n, data->kmu);
        double cf = u * fbl * fc->area;
        dvs[fc->cl1] += cf;
        if (fc->cl2 != -1)
            dvs[fc->cl2] -= cf;
    }

    for (auto& cl : grd->cells) {
        double poro = 1.0;
        result[cl->ind] = init[cl->ind] + tau / (poro * cl->volume) * dvs[cl->ind];
    }

    // std::cout << dvs[99] << std::endl;

    return result;
}

std::vector<double> solve_satur(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    switch (data->sat_setts->type) {
    case calc::models::SaturSolverType::TypeEnum::kExplicit:
        return solve_explicit(tau, init, data, grd);
    case calc::models::SaturSolverType::TypeEnum::kImplicit:
    default:
        return solve_explicit(tau, init, data, grd);
    }
}

}

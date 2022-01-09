#include "saturSolverNum.hpp"

#include "common/services/workRp.hpp"
#include "mesh/models/faceType.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

std::vector<double> solve_explicit(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    auto get_s = [&](const std::shared_ptr<mesh::models::Face> fc, double u) {
        return (u > 0.)
            ? (fc->cl2 == -1)
                ? fc->bound_satur
                : init[fc->cl2]
            : init[fc->cl1];
    };

    auto get_eps = [&]() {
        switch (data->contour_press_bound_type) {
        case common::models::BoundCondType::kImpermeable: {
            return 1.0 / data->perm_fract;
        }
        case common::models::BoundCondType::kConst:
        default:
            return 1.0;
        }
    };

    std::vector<double> result(init.size(), 0.);
    std::vector<double> dvs(grd->cells.size(), 0.);

    for (auto& fc : grd->faces) {
        double u = fc->u;
        double s = get_s(fc, u);
        double fbl = cs::rp::get_fbl(s, data->rp_n, data->kmu);
        double cf = mm::FaceType::is_top_bot(fc->type)
            ? 1.0 / (2.0 * data->get_m())
            : 1.0;
        double val = u * fbl * fc->area * cf;
        dvs[fc->cl1] += val;
        if (fc->cl2 != -1)
            dvs[fc->cl2] -= val;
    }

    double eps = get_eps();
    for (auto& cl : grd->cells) {
        result[cl->ind] = init[cl->ind] + tau / (eps * cl->volume) * dvs[cl->ind];
    }

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

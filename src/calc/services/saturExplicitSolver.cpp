#include "saturExplicitSolver.hpp"

#include "common/services/workRp.hpp"
#include "saturSolverShared.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

std::vector<double> SaturExplicitSolverService::solve(
    double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data,
    const std::shared_ptr<mesh::models::Grid> grd)
{
    std::vector<double> result(init.size(), 0.);
    std::vector<double> dvs(grd->cells.size(), 0.);

    for (auto& fc : grd->faces) {
        double u = fc->u;
        double s = get_s(init, fc, u);
        double fbl = cs::rp::get_fbl(s, data->rp_n, data->kmu);
        double cf = satur_solver_shared::get_face_cf(data, fc);
        double val = u * fbl * fc->area * cf;
        dvs[fc->cl1] += val;
        if (fc->cl2 != -1)
            dvs[fc->cl2] -= val;
    }

    // double eps = get_eps();
    for (auto& cl : grd->cells) {
        result[cl->ind] = init[cl->ind] + tau / (data->eps * cl->volume) * dvs[cl->ind];
    }

    return result;
}

double SaturExplicitSolverService::get_s(const std::vector<double>& init,
    const std::shared_ptr<mesh::models::Face> fc, double u)
{
    return (u > 0.)
        ? (fc->cl2 == -1)
            ? fc->bound_satur
            : init[fc->cl2]
        : init[fc->cl1];
}

}

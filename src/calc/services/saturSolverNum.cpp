#include "saturSolverNum.hpp"

#include "calc/services/saturExplicitSolver.hpp"
#include "calc/services/saturImplicitSolver.hpp"

#include "logging/logger.hpp"

namespace ble::src::calc::services {

std::vector<double> solve_explicit(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    return SaturExplicitSolverService::solve(tau, init, data, grd);
}

std::vector<double> solve_implicit(double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data,
    const std::shared_ptr<mesh::models::Grid> grd, bool need_precise)
{
    auto solver = std::make_shared<SaturImplicitSolverService>();
    return solver->solve(tau, init, data, grd, need_precise);
}

std::vector<double> solve_satur(const double tau, bool need_precise, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mesh::models::Grid> grd)
{
    switch (data->sat_setts->type) {
    case calc::models::SaturSolverType::TypeEnum::kExplicit:
        return solve_explicit(tau, init, data, grd);
    case calc::models::SaturSolverType::TypeEnum::kImplicit:
        return solve_implicit(tau, init, data, grd, need_precise);
    default:
        return solve_explicit(tau, init, data, grd);
    }
}

}

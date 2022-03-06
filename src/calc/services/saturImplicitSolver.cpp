#include "saturImplicitSolver.hpp"

namespace ble::src::calc::services {

// SaturImplicitSolverService::SaturImplicitSolverService( //const std::shared_ptr<common::models::SolverData> data,
//     const std::shared_ptr<mesh::models::Grid> grd)
// {
//     // m_data = data;
//     m_grd = grd;
// }

// SaturImplicitSolverService::~SaturImplicitSolverService()
// {
// }

std::vector<double> SaturImplicitSolverService::solve(double tau, int simple_count,
    const std::vector<double>& init, const std::shared_ptr<mesh::models::Grid> grd)
{
    m_tau = tau;
    m_simple_count = simple_count;
    m_init = init;
    m_grd = grd;

    m_ret.resize(grd->cells.size());

    return init;
}

void SaturImplicitSolverService::build_simple()
{

}

double SaturImplicitSolverService::operA(int cind)
{
    double s = m_init[cind];
}

}

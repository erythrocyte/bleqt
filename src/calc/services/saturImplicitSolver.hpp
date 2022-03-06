#ifndef BLE_SRC_SATURIMPLICITSOLVERSERVICE_H_
#define BLE_SRC_SATURIMPLICITSOLVERSERVICE_H_

#include "calc/models/diagMatrix.hpp"
#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {
class SaturImplicitSolverService {
public:
    std::vector<double> solve(double tau, int simple_count, const std::vector<double>& init,
        const std::shared_ptr<mesh::models::Grid> grd);

private:
    // std::shared_ptr<common::models::SolverData> m_data;
    std::shared_ptr<mesh::models::Grid> m_grd;
    int m_simple_count;
    double m_tau;
    std::vector<double> m_init;
    models::DiagMat m_ret;

    SaturImplicitSolverService() { } //const std::shared_ptr<common::models::SolverData> data,
    // const std::shared_ptr<mesh::models::Grid> grd);
    ~SaturImplicitSolverService() { }

    void build_simple();
    double operA(int cind);
};
}

#endif
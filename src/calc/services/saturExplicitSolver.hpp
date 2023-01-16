#ifndef BLE_SRC_SATUREXPLICITSOLVERSERVICE_H_
#define BLE_SRC_SATUREXPLICITSOLVERSERVICE_H_

#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {

class SaturExplicitSolverService {
public:
    static std::vector<double> solve(double tau, const std::vector<double>& init,
        const std::shared_ptr<common::models::SolverData> data,
        const std::shared_ptr<mesh::models::Grid> grd);

private:
    SaturExplicitSolverService() { }
    ~SaturExplicitSolverService() { }

    static double get_s(const std::vector<double>& init, const std::shared_ptr<mesh::models::Face> fc, double u);
};
}

#endif
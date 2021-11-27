#ifndef BLE_SRC_SATURSOLVERNUM_H_
#define BLE_SRC_SATURSOLVERNUM_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {

std::vector<double> solve_satur(const double tau, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mesh::models::Grid> grd);

}

#endif

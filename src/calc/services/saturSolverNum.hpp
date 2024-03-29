#ifndef BLE_SRC_SATURSOLVERNUM_H_
#define BLE_SRC_SATURSOLVERNUM_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace mm = ble::src::mesh::models;

namespace ble::src::calc::services {

std::vector<double> solve_satur(const double tau, bool need_precise, const std::vector<double>& init,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mm::Grid> grd);

}

#endif

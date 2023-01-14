#ifndef BLE_SRC_PRESSURE_SOLVER_H_
#define BLE_SRC_PRESSURE_SOLVER_H_

#include <iostream>
#include <tuple>
#include <vector>

#include "common/models/gridType.hpp"
#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace mm = ble::src::mesh::models;

namespace ble::src::calc::services {

std::vector<double> solve_press(const std::shared_ptr<mm::Grid> grd, const std::vector<double>& s,
    const std::shared_ptr<common::models::SolverData> data);
std::vector<double> calc_press_exact(const std::shared_ptr<mm::Grid> grd,
    const std::shared_ptr<common::models::SolverData> data);
void calc_u(const std::vector<double>& p, const std::vector<double>& s,
    const std::shared_ptr<common::models::SolverData> data,
    std::shared_ptr<mm::Grid> grd);
std::tuple<int, double> calc_residual(const std::shared_ptr<mm::Grid> grd,
    const std::shared_ptr<common::models::SolverData> params);

}

#endif

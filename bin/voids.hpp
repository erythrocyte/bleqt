#ifndef BLE_BIN_VOIDS_H
#define BLE_BIN_VOIDS_H

#include <iostream>
#include <memory>

#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace cm = ble::src::common::models;
namespace msm = ble::src::mesh::models;

namespace ble::bin {

std::shared_ptr<cm::SolverData> get_solver_data();
std::shared_ptr<msm::Grid> get_grid(const std::shared_ptr<cm::SolverData> params);
void solve(const std::shared_ptr<cm::SolverData> params, const std::shared_ptr<msm::Grid> grd);
void update_progress(double perc);

}

#endif
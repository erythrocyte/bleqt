#ifndef BLE_SRC_CALC_SERVICES_WORKTIMESTEP_H_
#define BLE_SRC_CALC_SERVICES_WORKTIMESTEP_H_

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {

double get_time_step(const std::shared_ptr<mesh::models::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::SolverData> data,
    std::map<std::string, double>& tt);

}

#endif

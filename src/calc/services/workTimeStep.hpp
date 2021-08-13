#ifndef BLE_SRC_WORKTIMESTEP_H_
#define BLE_SRC_WORKTIMESTEP_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/inputData.hpp"
#include "mesh/models/grid.hpp"

namespace ble_src::calc::services {

double get_time_step(const std::shared_ptr<mesh::models::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::InputData> data);

}

#endif

#ifndef BLE_SRC_PRESSURE_SOLVER_H_
#define BLE_SRC_INPUTDATA_H_

#include <iostream>
#include <vector>

#include "common/models/physData.hpp"
#include "mesh/models/grid.hpp"

namespace mm = ble_src::mesh::models;

namespace ble_src {

std::vector<double> solve_press(const std::shared_ptr<mm::Grid> grd, const std::vector<double>& s,
    const std::shared_ptr<common::models::PhysData> data);
void calc_u(const std::vector<double>& p, const std::vector<double>& s,
    const std::shared_ptr<common::models::PhysData> data,
    std::shared_ptr<mm::Grid> grd);

}

#endif

#ifndef BLE_SRC_PRESSURE_SOLVER_H_
#define BLE_SRC_INPUTDATA_H_

#include <iostream>
#include <vector>

#include "grid.hpp"
#include "physData.hpp"

namespace ble_src {

std::vector<double> solve_press(const std::shared_ptr<Grid> grd, const std::vector<double>& s, const std::shared_ptr<PhysData> data);

}

#endif

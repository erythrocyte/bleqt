#ifndef BLE_SRC_WORKTIMESTEP_H_
#define BLE_SRC_WORKTIMESTEP_H_

#include <iostream>
#include <memory>
#include <vector>

#include "grid.hpp"
#include "inputData.hpp"

namespace ble_src {

double get_time_step(const std::shared_ptr<Grid> grd, const std::vector<double>&s, const std::shared_ptr<InputData> data);

}


#endif

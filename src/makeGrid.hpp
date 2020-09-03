#ifndef BLE_SRC_MAKEGRID_H_
#define BLE_SRC_MAKEGRID_H_

#include <iostream>
#include <memory>
#include "inputData.hpp"
#include "grid.hpp"

namespace ble_src {

std::shared_ptr<Grid> make_grid(const std::shared_ptr<InputData> data);

}

#endif

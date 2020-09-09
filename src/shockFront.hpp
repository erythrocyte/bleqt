#ifndef BLE_SRC_SHOCKFRONT_H_
#define BLE_SRC_SHOCKFRONT_H_

#include <iostream>
#include <memory>

#include "physData.hpp"

namespace ble_src{

double get_shock_front(const std::shared_ptr<PhysData> data);

}


#endif

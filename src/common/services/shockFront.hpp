#ifndef BLE_SRC_SHOCKFRONT_H_
#define BLE_SRC_SHOCKFRONT_H_

#include <iostream>
#include <memory>

#include "common/models/physData.hpp"

namespace ble_src::common::services::shock_front {

double get_shock_front(const std::shared_ptr<common::models::PhysData> data);

}

#endif

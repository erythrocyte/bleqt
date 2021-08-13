#ifndef BLE_GUI_WORKPARAM_H_
#define BLE_GUI_WORKPARAM_H_

#include <iostream>
#include <memory>

#include "mesh/models/grid.hpp"

namespace ble_src::calc::services {
double getULiqInject(const std::shared_ptr<mesh::models::Grid> grd);
}

#endif

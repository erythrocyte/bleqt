#ifndef BLE_SRC_MESH_SERVICES_MAKEGRID_H_
#define BLE_SRC_MESH_SERVICES_MAKEGRID_H_

#include <iostream>
#include <memory>

#include "common/models/inputData.hpp"
#include "mesh/models/grid.hpp"

namespace ble_src::mesh::services {

std::shared_ptr<models::Grid> make_grid(const std::shared_ptr<common::models::InputData> data);

}

#endif

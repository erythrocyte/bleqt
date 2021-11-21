#ifndef BLE_SRC_CALC_MODELS_BLERESULTDATA_H_
#define BLE_SRC_CALC_MODELS_BLERESULTDATA_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/dynamicData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::models {
class BleResultData {
public:
    std::shared_ptr<mesh::models::Grid> grd;
    std::vector<std::shared_ptr<common::models::DynamicData>> data;
};
} // namespace ble::src

#endif
#ifndef BLE_SRC_CALC_MODELS_AVERFWSAVEDATA_H_
#define BLE_SRC_CALC_MODELS_AVERFWSAVEDATA_H_

#include <iostream>
#include <memory>

#include "common/models/fwData.hpp"

namespace ble::src::calc::models {
class AverFwSaveData {
public:
    double m;
    double s_const;
    std::shared_ptr<common::models::FwData> data;
};
}

#endif
#ifndef BLE_SRC_COMMON_MODELS_DATA_H_
#define BLE_SRC_COMMON_MODELS_DATA_H_

#include <iostream>
#include <memory>

#include "physData.hpp"

namespace ble::src::common::models {

class Data {
public:
    std::shared_ptr<PhysData> phys;
    double perm_res;
    double perm_fract;
    double poro_fract;
    double l;
    double r;
    double rw;
    double delta;
    double period;
};

}

#endif

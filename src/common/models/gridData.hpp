#ifndef BLE_SRC_COMMON_MODELS_GRIDDATA_H_
#define BLE_SRC_COMMON_MODELS_GRIDDATA_H_

#include "gridType.hpp"

namespace ble_src::common::models {

class GridData {
public:
    double l;
    double n;

    GridType::TypeEnum type;
};

}

#endif

#ifndef BLE_SRC_COMMON_MODELS_GRIDDATA_H_
#define BLE_SRC_COMMON_MODELS_GRIDDATA_H_

#include "gridType.hpp"

namespace ble::src::common::models {

class GridData {
public:
    double rw;
    double rc;
    double n;

    GridType::TypeEnum type;

    double get_lenght() { return rc - rw; }
};

}

#endif

#ifndef BLE_SRC_COMMON_MODELS_MESHSETTINGS_H_
#define BLE_SRC_COMMON_MODELS_MESHSETTINGS_H_

#include "gridType.hpp"

namespace ble::src::common::models {

class MeshSettings {
public:
    double n;
    GridType::TypeEnum type;    
};

}

#endif

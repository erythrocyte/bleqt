#ifndef BLE_SRC_COMMON_MODELS_PHYSDATA_H_
#define BLE_SRC_COMMON_MODELS_PHYSDATA_H_

namespace ble::src::common::models {

class PhysData {
public:
    double kmu; // = mw / moil;
    double n_oil;
    double n_wat;
    double poro = 1.;
    double perm = 1.;
};

}

#endif

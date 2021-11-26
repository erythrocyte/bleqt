#ifndef BLE_SRC_COMMON_MODELS_PHYSDATA_H_
#define BLE_SRC_COMMON_MODELS_PHYSDATA_H_

namespace ble::src::common::models {

class PhysData {
public:
    double mu_wat;
    double mu_oil;
    double n_oil;
    double n_wat;

    double get_kmu() { return mu_wat / mu_oil; }
};

}

#endif

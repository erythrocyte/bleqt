#ifndef BLE_SRC_COMMON_MODELS_SCALEDATA_H_
#define BLE_SRC_COMMON_MODELS_SCALEDATA_H_

#include <iostream>
#include <memory>

namespace ble::src::common::models {

class ScaleData {
public:
    double r0;
    double mu0;
    double poro0;
    double perm0;
    double dp;
    double p0;

    double u0() { return (perm0 / mu0) * dp / r0; }
    double t0() { return poro0 * r0 / u0(); }
};

}

#endif

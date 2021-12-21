#ifndef BLE_SRC_COMMON_MODELS_WELLWORKPARAMS_H_
#define BLE_SRC_COMMON_MODELS_WELLWORKPARAMS_H_

#include <iostream>

namespace ble::src::common::models {

class WellWorkParams {
public:
    double t = 0.0;
    double qw = 0.0;
    double ql = 0.0;
    double qo = 0.0;
    double fw = 0.0;
    double fw_shore = 0.0;
};

} // namespace ble::src

#endif

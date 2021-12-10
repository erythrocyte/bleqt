#ifndef BLE_SRC_COMMON_MODELS_FWDATA_H_
#define BLE_SRC_COMMON_MODELS_FWDATA_H_

#include <iostream>

namespace ble::src::common::models {
class FwData {
public:
    FwData() { }

    ~FwData() { }

    double t;
    double fw_num;
    double fw_an;
    double sav_num;
    double sav_an;
};
}

#endif
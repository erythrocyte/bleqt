#ifndef BLE_SRC_COMMON_MODELS_FWDATA_H_
#define BLE_SRC_COMMON_MODELS_FWDATA_H_

#include <iostream>

namespace ble::src::common::models {
class FwData {
public:
    FwData() { }

    ~FwData() { }

    double pv;
    double fw_num_well;
    double fw_num_shore;
    double sav_num;
    double sav_an_shore;
};
}

#endif
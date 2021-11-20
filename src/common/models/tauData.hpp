#ifndef BLE_SRC_COMMON_MODELS_TAUDATA_H_
#define BLE_SRC_COMMON_MODELS_TAUDATA_H_

#include <iostream>

namespace ble::src::common::models {
class TauData {
public:
    TauData(double time, double tau)
    {
        this->time = time;
        this->tau = tau;
    }

    ~TauData() { }

    double time;
    double tau;
};
}

#endif
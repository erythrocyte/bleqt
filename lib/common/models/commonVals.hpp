
#ifndef BLE_SRC_COMMON_MODELS_COMMONVALS_H_
#define BLE_SRC_COMMON_MODELS_COMMONVALS_H_

#include <cmath>

namespace ble::src::common::models {

class CommonVals {
public:
    static double constexpr EMPTY_VAL = -999999.0;

    static bool is_empty(double val) { return std::abs(val - EMPTY_VAL) < 1e-8; }

private:
    CommonVals() { }
    ~CommonVals() { }
};

}

#endif
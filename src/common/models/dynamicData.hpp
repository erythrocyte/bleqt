#ifndef BLE_SRC_COMMON_MODELS_DYNAMICDATA_H_
#define BLE_SRC_COMMON_MODELS_DYNAMICDATA_H_

#include <iostream>
#include <tuple>
#include <vector>

namespace ble_src::common::models {

class DynamicData {
public:
    double t;
    std::vector<double> p;
    std::vector<double> s;

    std::vector<std::tuple<double, double>> s_an;
};

} // namespace ble_src

#endif

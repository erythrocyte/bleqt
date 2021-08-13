#ifndef BLE_SRC_SATURSOLVERANALYTIC_H_
#define BLE_SRC_SATURSOLVERANALYTIC_H_

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

#include "common/models/inputData.hpp"

namespace ble_src::calc::services {
std::vector<std::tuple<double, double>> get_satur_exact(const double sc, const double u,
    const std::shared_ptr<common::models::InputData> data);
}

#endif

#ifndef BLE_SRC_COMMON_SERVICES_COMMONMATH_H_
#define BLE_SRC_COMMON_SERVICES_COMMONMATH_H_

#include <iostream>
#include <memory>

#include "common/models/dataDistribution.hpp"

namespace ble::src::common::services {
double get_value_lin_approx(const double x0, const double y0, const double x1,
    const double y1, const double val);
double get_value_lin_approx(const std::shared_ptr<models::DataDistribution> cond, const double v);

}

#endif

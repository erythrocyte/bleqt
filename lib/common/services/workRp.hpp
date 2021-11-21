#ifndef BLE_SRC_WORKRP_H_
#define BLE_SRC_WORKRP_H_

#include <iostream>
#include <memory>

#include "common/models/physData.hpp"

namespace ble::src::common::services::rp {

double get_kw(double s, const std::shared_ptr<common::models::PhysData> data);
double get_koil(double s, const std::shared_ptr<common::models::PhysData> data);
double get_fbl(double s, const std::shared_ptr<common::models::PhysData> data);
double get_sigma(double s, const std::shared_ptr<common::models::PhysData> data);
double get_dfbl(double s, const std::shared_ptr<common::models::PhysData> data);

} // namespace ble::src

#endif

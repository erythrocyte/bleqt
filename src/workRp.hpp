#ifndef BLE_SRC_WORKRP_H_
#define BLE_SRC_WORKRP_H_

#include <iostream>
#include <memory>

#include "physData.hpp"

namespace ble_src
{
    double get_kw(double s, const std::shared_ptr<PhysData> data);
    double get_koil(double s, const std::shared_ptr<PhysData> data);
    double get_fbl(double s, const std::shared_ptr<PhysData> data);
    double get_sigma(double s, const std::shared_ptr<PhysData> data);
    double get_dfbl(double s, const std::shared_ptr<PhysData> data);

} // namespace ble_src

#endif

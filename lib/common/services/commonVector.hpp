#ifndef BLE_SRC_COMMON_SERVICES_COMMONVECTOR_H_
#define BLE_SRC_COMMON_SERVICES_COMMONVECTOR_H_

#include <iostream>
#include <vector>

namespace ble::src::common::services {

std::vector<double> make_vector(double begin, double end, int n);

}

#endif
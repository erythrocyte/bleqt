#ifndef BLE_SRC_COMMON_SERVICES_COMMONVECTOR_H_
#define BLE_SRC_COMMON_SERVICES_COMMONVECTOR_H_

#include <iostream>
#include <vector>

namespace ble::src::common::services::common_vector {

std::vector<double> make_vector(double begin, double end, int n);

std::vector<double> subtract(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> add(const std::vector<double>& v1, const std::vector<double>& v2);
double max_abs(const std::vector<double>& v);

void mult_scal(std::vector<double>& v, double s);

}

#endif
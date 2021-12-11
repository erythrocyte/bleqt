#ifndef BLE_SRC_CALC_SERVICES_SATURAVERSERVICE_H_
#define BLE_SRC_CALC_SERVICES_SATURAVERSERVICE_H_

#include <iostream>
#include <vector>
#include <memory>

#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {
class SaturAverService {
public:
    static double get_satur_aver_analytic(int n, double fw, double kmu);
    static double get_satur_aver_num(const std::shared_ptr<mesh::models::Grid> grd, const std::vector<double>& s);
};

} // namespace ble::src::calc::services

#endif
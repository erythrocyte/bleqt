#ifndef BLE_SRC_COMMON_SERVICES_BOUNDSOURCESERVICE_H_
#define BLE_SRC_COMMON_SERVICES_BOUNDSOURCESERVICE_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common/models/commonVals.hpp"
#include "common/models/dataDistribution.hpp"

namespace ble::src::common::services {

class DataDistributionService {
public:
    static std::vector<std::shared_ptr<models::DataDistribution>> get_data_from_file(std::string& file_name);
    static std::vector<std::shared_ptr<models::DataDistribution>> get_data_from_const(
        double const_val, int len_right_prec, double x0, double x1);

    static double get_value(double x,
        const std::vector<std::shared_ptr<models::DataDistribution>>& data,
        double def_val = models::CommonVals::EMPTY_VAL);

    static std::tuple<double, double> get_range(double minx_grd, double maxx_grd,
        const std::vector<std::shared_ptr<models::DataDistribution>>& data);
};

}

#endif
#ifndef BLE_SRC_COMMON_SERVICES_BOUNDSOURCESERVICE_H_
#define BLE_SRC_COMMON_SERVICES_BOUNDSOURCESERVICE_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common/models/dataDistribution.hpp"

namespace ble::src::common::services {

class DataDistributionService {
public:
    static std::vector<std::shared_ptr<models::DataDistribution>> get_data_from_file(std::string& file_name);
    static std::vector<std::shared_ptr<models::DataDistribution>> get_data_from_const(
        double const_val, int len_right_prec, double x0, double x1);
};

}

#endif
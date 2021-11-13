#ifndef BLE_SRC_COMMON_MODELS_BOUNDCONDDATA_H_
#define BLE_SRC_COMMON_MODELS_BOUNDCONDDATA_H_

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

#include "boundCondType.hpp"
#include "dataDistribution.hpp"
#include "dataDistributionType.hpp"

namespace ble::src::common::models {
class BoundCondData {
public:
    BoundCondData() { }
    ~BoundCondData()
    {
        top_bot_bound_u.clear();
        top_bot_bound_s.clear();
        initial_s.clear();
    }

    std::vector<std::shared_ptr<DataDistribution>> top_bot_bound_u;
    std::vector<std::shared_ptr<DataDistribution>> top_bot_bound_s;
    std::vector<std::shared_ptr<DataDistribution>> initial_s;
    BoundCondType::TypeEnum contour_press_bound_type;
    DataDistributionType::TypeEnum top_bot_bound_u_type;
    DataDistributionType::TypeEnum top_bot_bound_s_type;
    DataDistributionType::TypeEnum initial_satur_type;
    double bound_satur;

};
}

#endif
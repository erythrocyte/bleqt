#ifndef BLE_SRC_COMMON_MODELS_BOUNDCONDDATA_H_
#define BLE_SRC_COMMON_MODELS_BOUNDCONDDATA_H_

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

#include "dataDistribution.hpp"
#include "dataDistributionType.hpp"

namespace ble::src::common::models {
class BoundCondData {
public:
    BoundCondData() { }
    ~BoundCondData()
    {
        fract_shore_s.clear();
        initial_s.clear();
        fract_shore_q.clear();
    }

    // initial in fract
    DataDistributionType::TypeEnum initial_satur_type;
    std::vector<std::shared_ptr<DataDistribution>> initial_s;

    // fract end
    bool fract_end_imperm;
    double fract_end_satur;

    // fract shore
    bool fract_shore_imperm;
    DataDistributionType::TypeEnum fract_shore_s_type;
    std::vector<std::shared_ptr<DataDistribution>> fract_shore_s;
    DataDistributionType::TypeEnum fract_shore_q_type;
    std::vector<std::shared_ptr<DataDistribution>> fract_shore_q;
    double pc;
    double fract_end_press;
    bool use_q;

    // well
    double pw;
    double sw;
};
}

#endif
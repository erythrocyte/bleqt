#ifndef BLE_SRC_COMMON_MODELS_BOUNDCONDDATA_H_
#define BLE_SRC_COMMON_MODELS_BOUNDCONDDATA_H_

#include <iostream>
#include <memory>
#include <vector>
#include <tuple>

#include "boundCondType.hpp"
#include "boundSourceCond.hpp"

namespace ble::src::common::models {
class BoundCondData {
public:
    BoundCondData() { }
    ~BoundCondData()
    {
        bound_sources.clear();
    }

    std::vector<std::shared_ptr<BoundSourceCond>> bound_sources;
    BoundCondType::TypeEnum bound_type;

    double get_value(double x, double def_val = -99999.0);

    std::tuple<double, double> get_range(double minx_grd, double maxx_grd);
};
}

#endif
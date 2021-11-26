#ifndef BLE_SRC_COMMON_SERVICES_DIMENSIONLESSSERVICE_H_
#define BLE_SRC_COMMON_SERVICES_DIMENSIONLESSSERVICE_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common/models/inputData.hpp"
#include "common/models/scaleData.hpp"
#include "common/models/solverData.hpp"

namespace ble::src::common::services {

class DimensionlessService {
public:
    std::tuple<std::shared_ptr<models::ScaleData>, std::shared_ptr<models::SolverData>> make_dimless(
        const std::shared_ptr<models::InputData> params);
};

}

#endif
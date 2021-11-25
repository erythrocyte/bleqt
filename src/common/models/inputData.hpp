#ifndef BLE_SRC_COMMON_MODELS_INPUTDATA_H_
#define BLE_SRC_COMMON_MODELS_INPUTDATA_H_

#include <iostream>
#include <memory>

#include "calc/models/saturSolverSettings.hpp"
#include "gridData.hpp"
// #include "modelData.hpp"
// #include "physData.hpp"
#include "data.hpp"
#include "boundCondData.hpp"

namespace ble::src::common::models {

class InputData {
public:
    // std::shared_ptr<PhysData> phys = std::make_shared<PhysData>();
    // std::shared_ptr<ModelData> model = std::make_shared<ModelData>();
    std::shared_ptr<Data> data = std::make_shared<Data>();
    std::shared_ptr<GridData> grd = std::make_shared<GridData>();
    std::shared_ptr<calc::models::SaturSolverSetts> satSetts = std::make_shared<calc::models::SaturSolverSetts>();
    std::shared_ptr<BoundCondData> bound = std::make_shared<BoundCondData>();
};

}

#endif

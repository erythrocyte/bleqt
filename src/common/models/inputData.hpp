#ifndef BLE_SRC_COMMON_MODELS_INPUTDATA_H_
#define BLE_SRC_COMMON_MODELS_INPUTDATA_H_

#include <iostream>
#include <memory>

#include "boundCondData.hpp"
#include "calc/models/saturSolverSettings.hpp"
#include "data.hpp"
#include "meshSettings.hpp"
#include "shockFrontSettings.hpp"

namespace ble::src::common::models {

class InputData {
public:
    std::shared_ptr<Data> data = std::make_shared<Data>();
    std::shared_ptr<BoundCondData> bound = std::make_shared<BoundCondData>();
    std::shared_ptr<MeshSettings> mesh_setts = std::make_shared<MeshSettings>();
    std::shared_ptr<ShockFrontSettings> sc_setts = std::make_shared<ShockFrontSettings>();
    std::shared_ptr<calc::models::SaturSolverSetts> sat_setts = std::make_shared<calc::models::SaturSolverSetts>();
};

}

#endif

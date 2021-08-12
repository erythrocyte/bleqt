#ifndef BLE_SRC_COMMON_MODELS_INPUTDATA_H_
#define BLE_SRC_COMMON_MODELS_INPUTDATA_H_

#include <iostream>
#include <memory>

#include "gridData.hpp"
#include "modelData.hpp"
#include "physData.hpp"
#include "saturSolverSettings.hpp"

namespace ble_src::common::models {

class InputData {
public:
    std::shared_ptr<PhysData> phys = std::make_shared<PhysData>();
    std::shared_ptr<ModelData> model = std::make_shared<ModelData>();
    std::shared_ptr<GridData> grd = std::make_shared<GridData>();
    std::shared_ptr<SaturSolverSetts> satSetts = std::make_shared<SaturSolverSetts>();
};

}

#endif

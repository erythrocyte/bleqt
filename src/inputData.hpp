#ifndef BLE_SRC_INPUTDATA_H_
#define BLE_SRC_INPUTDATA_H_

#include <iostream>
#include <memory>

#include "physData.hpp"
#include "modelData.hpp"
#include "gridData.hpp"
#include "saturSolverSettings.hpp"

namespace ble_src{

class InputData {
	public:
		std::shared_ptr<PhysData> phys = std::make_shared<PhysData>();
		std::shared_ptr<ModelData> model = std::make_shared<ModelData>();
		std::shared_ptr<GridData> grd = std::make_shared<GridData>();
		std::shared_ptr<SaturSolverSetts> satSetts = std::make_shared<SaturSolverSetts>();
};

}

#endif

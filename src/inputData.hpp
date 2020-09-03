#ifndef BLE_SRC_INPUTDATA_H_
#define BLE_SRC_INPUTDATA_H_

#include <iostream>
#include <memory>


namespace ble_src{

class InputData {
	public:
		std::shared_ptr<PhysData> phys (new PhysData());
		std::shared_ptr<ModelData> phys (new ModelData());
		std::shared_ptr<GridData> phys (new GridData());
}

}

#endif

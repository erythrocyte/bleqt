#ifndef BLE_SRC_SATURSOLVERSETTINGS_H_
#define BLE_SRC_SATURSOLVERSETTINGS_H_

#include "saturSolverType.hpp"

namespace ble_src {

class SaturSolverSetts { 
	public:
		double cur_val;
		int pN; // pressUpdateTimeStepCount;
		SaturSolverType type;
}

}

#endif

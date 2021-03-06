#ifndef BLE_SRC_GRID_H_
#define BLE_SRC_GRID_H_

#include <iostream>
#include <memory>
#include <vector>

#include "face.hpp"
#include "cell.hpp"

namespace ble_src {

class Grid {
	public:
		std::vector<std::shared_ptr<Face>> faces;
		std::vector<std::shared_ptr<Cell>> cells;
};

}

#endif

#ifndef BLE_SRC_MESH_MODELS_CELL_H_
#define BLE_SRC_MESH_MODELS_CELL_H_

#include <iostream>
#include <vector>

namespace ble::src::mesh::models {

class Cell {
	public:
		int ind;

		double xl;
		double xr;
		double cntr;

		std::vector<int> faces;

		double volume;

		double poro;
		double perm;
};

}

#endif

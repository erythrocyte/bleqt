#ifndef BLE_SRC_CELL_H_
#define BLE_SRC_CELL_H_

namespace ble_src {

class Cell {
	public:
		int ind;

		double xl;
		double xr;
		double cntr;

		int fl;
		int fr;

		double volume;

		double poro;
		double perm;
};

}

#endif

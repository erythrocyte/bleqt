#ifndef BLE_SRC_FACE_H_
#define BLE_SRC_FACE_H_

namespace ble_src {

class Face {
	public:
		int ind;
		double x;

		int cl1;
		int cl2 = -1;

		double u;

		double area = 1.;
};

}

#endif

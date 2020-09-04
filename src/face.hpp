#ifndef BLE_SRC_FACE_H_
#define BLE_SRC_FACE_H_

#include "faceType.hpp"

namespace ble_src {

class Face {
	public:
		int ind;
		double x;

		int cl1;
		int cl2 = -1;

		double u;

		double area = 1.;

		double bound_press = 0.;

		FaceType type;
};

}

#endif

#ifndef BLE_SRC_MESH_MODELS_FACE_H_
#define BLE_SRC_MESH_MODELS_FACE_H_

#include "faceType.hpp"

namespace ble::src::mesh::models {

class Face {
	public:
		int ind;
		double x;

		int cl1;
		int cl2 = -1;

		double u;

		double area = 1.;

		double bound_press = 0.;
		double bound_satur = 0.;

		FaceType type;
};

}

#endif

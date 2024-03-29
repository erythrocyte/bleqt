#ifndef BLE_SRC_MESH_MODELS_FACE_H_
#define BLE_SRC_MESH_MODELS_FACE_H_

#include "faceType.hpp"

namespace ble::src::mesh::models {

class Face {
	public:
		int ind;
		double cntr;

		int cl1;
		int cl2 = -1;

		double u;

		double area = 0.0;

		double bound_press = 0.;
		double bound_satur = 0.;
		double bound_u = 0.0;

		FaceType::TypeEnum type;
};

}

#endif

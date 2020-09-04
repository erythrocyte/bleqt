#ifndef BLE_SRC_WORKSIGMA_H_
#define BLE_SRC_WORKSIGMA_H_

#include <iostream>
#include <memory>
#include <vector>

#include "face.hpp"
#include "physData.hpp"


namespace ble_src {

double get_face_sigma(const std::shared_ptr<Face> fc, const std::vector<double> s, const std::shared_ptr<PhysData> data);

}

#endif

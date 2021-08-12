#ifndef BLE_SRC_WORKSIGMA_H_
#define BLE_SRC_WORKSIGMA_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/physData.hpp"
#include "mesh/models/face.hpp"
#include "mesh/models/grid.hpp"

namespace ble_src {
double get_face_sigma(const std::shared_ptr<mesh::models::Face> fc, const std::vector<double> s,
    const std::shared_ptr<common::models::PhysData> data, const std::shared_ptr<mesh::models::Grid> grd);

} // namespace ble_src

#endif

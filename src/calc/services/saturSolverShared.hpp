#ifndef BLE_SRC_CALC_SERVICES_SATURSOLVERSHARED_H_
#define BLE_SRC_CALC_SERVICES_SATURSOLVERSHARED_H_

#include <iostream>
#include <memory>

#include "common/models/solverData.hpp"
#include "mesh/models/face.hpp"

namespace ble::src::calc::services::satur_solver_shared {

double get_face_cf(const std::shared_ptr<common::models::SolverData> data,
    const std::shared_ptr<mesh::models::Face> fc);

}

#endif
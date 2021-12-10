#ifndef BLE_SRC_MESH_MODELS_GRID_H_
#define BLE_SRC_MESH_MODELS_GRID_H_

#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

#include "cell.hpp"
#include "face.hpp"

namespace ble::src::mesh::models {

class Grid {
public:
    std::vector<std::shared_ptr<Face>> faces;
    std::vector<std::shared_ptr<Cell>> cells;

    double sum_volume = 0.0;

    std::tuple<double, double> get_min_max();
};

}

#endif

#ifndef BLE_GUI_WORKPARAM_H_
#define BLE_GUI_WORKPARAM_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/physData.hpp"
#include "common/models/wellWorkParams.hpp"
#include "mesh/models/grid.hpp"

namespace mm = ble_src::mesh::models;

namespace ble_src::calc::services {
double getULiqInject(const std::shared_ptr<mm::Grid> grd);
std::shared_ptr<common::models::WellWorkParams> calc_well_work_param(const std::shared_ptr<mm::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::PhysData> data, double t);
}

#endif

#ifndef BLE_SRC_CALC_SERVICES_WORKPARAM_H_
#define BLE_SRC_CALC_SERVICES_WORKPARAM_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/gridType.hpp"
#include "common/models/solverData.hpp"
#include "common/models/wellWorkParams.hpp"
#include "mesh/models/grid.hpp"

namespace mm = ble::src::mesh::models;
namespace cm = ble::src::common::models;

namespace ble::src::calc::services {

double getULiqInject(const std::shared_ptr<mm::Grid> grd, cm::GridType::TypeEnum grid_type);
std::shared_ptr<cm::WellWorkParams> calc_well_work_param(const std::shared_ptr<mm::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<cm::SolverData> data, double t);
double calc_q_analytic(const std::shared_ptr<mm::Grid> grd, const std::shared_ptr<cm::SolverData> data);

}

#endif

#ifndef BLE_SRC_CALC_SERVICES_SATURAVERSERVICE_H_
#define BLE_SRC_CALC_SERVICES_SATURAVERSERVICE_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {
class SaturAverService {
public:
    static double get_satur_aver_analytic(int n, double fw, double kmu);
    static double get_satur_aver_num(const std::shared_ptr<mesh::models::Grid> grd, const std::vector<double>& s);
    static double calc_sf_aver(double qw_bound, double ql_well, double s_prev, double tau,
        const std::shared_ptr<mesh::models::Grid> grd, const std::shared_ptr<common::models::SolverData> solver_data);
    static double calc_sf_aver_time_step(double u_bound, double s_bound,
        double u_well, double s_well, const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::SolverData> solver_data);
};

} // namespace ble::src::calc::services

#endif
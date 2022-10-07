#include "saturAverService.hpp"

#include <cmath>

#include "common/services/workRp.hpp"
#include "workTimeStep.hpp"

namespace ble::src::calc::services {

double SaturAverService::get_satur_aver_analytic(int n, double fw, double kmu)
{
    if (fw > 0.99)
        return 1.0;
    double a = std::pow((fw * kmu) / (1.0 - fw), 1.0 / n);
    return a / (1.0 + a);
}

double SaturAverService::get_satur_aver_num(const std::shared_ptr<mesh::models::Grid> grd, const std::vector<double>& s)
{
    double result = 0.0;
    for (auto& cl : grd->cells) {
        result += cl->volume * s[cl->ind];
    }

    return result / grd->sum_volume;
}

double SaturAverService::calc_sf_aver(double qw_bound, double ql_well, double s_prev, double tau,
    const std::shared_ptr<mesh::models::Grid> grd, const std::shared_ptr<common::models::SolverData> solver_data)
{
    double sv = grd->sum_volume;
    double cv = tau / solver_data->eps / sv / (2.0 * solver_data->m);
    double dq = qw_bound - ql_well * common::services::rp::get_fbl(s_prev, solver_data->rp_n, solver_data->kmu);
    double result = s_prev + dq * cv;

    // std::cout << "s_old = " << s_prev << ", s_new = "
    //           << result << "dq = " << dq << ", cv = " << cv
    //           << ", tau = " << tau << std::endl;
    return result;
}

double SaturAverService::calc_sf_aver_time_step(double u_bound, double s_bound,
    double u_well, double s_well, const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::SolverData> solver_data)
{
    double dfbl_bound = services::get_aver_dfbl(s_bound, s_bound, solver_data);
    double dfbl_well = services::get_aver_dfbl(s_well, s_well, solver_data);

    double ufdbl = u_bound * dfbl_bound - u_well * dfbl_well;

    double currant_value = 1.0; // m_data->sat_setts->cv;

    double poro = 1.0;
    double volume = grd->sum_volume;
    double result = currant_value * poro * volume / ufdbl;

    return result;
}

} // namespace ble::src::calc::services

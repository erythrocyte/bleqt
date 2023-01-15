#include "dimensionlessService.hpp"

#include <functional>

#include "common/models/dataDistribution.hpp"
#include "common/services/workRp.hpp"

namespace ble::src::common::services {

std::tuple<std::shared_ptr<models::ScaleData>, std::shared_ptr<models::SolverData>> DimensionlessService::make_dimless(
    const std::shared_ptr<models::InputData> params)
{
    auto result_scale = std::make_shared<models::ScaleData>();

    auto scale_x = [&](double x) {
        return x / result_scale->r0;
    };

    auto scale_p = [&](double p) {
        return (p - result_scale->p0) / result_scale->dp;
    };

    auto scale_q = [&](double q) {
        double q0 = result_scale->u0() * (result_scale->r0 * result_scale->r0);
        return q / q0;
    };

    auto scale_distr_func = [&](const std::vector<std::shared_ptr<models::DataDistribution>>& data,
                                std::function<double(double)> func) {
        std::vector<std::shared_ptr<models::DataDistribution>> result;

        for (auto const d : data) {
            auto item = std::make_shared<models::DataDistribution>();
            item->x0 = scale_x(d->x0);
            item->x1 = scale_x(d->x1);
            item->v0 = func(d->v0);
            item->v1 = func(d->v1);
            result.push_back(item);
        }

        return result;
    };

    double p_max = params->bound->fract_end_press;

    if (params->bound->use_q) {
        double q_max = params->bound->fract_shore_q[0]->v0;

        for (auto fsq : params->bound->fract_shore_q) {
            if (fsq->v0 > q_max)
                q_max = fsq->v0;

            if (fsq->v1 > q_max)
                q_max = fsq->v1;
        }

        double s_max = params->bound->fract_shore_s[0]->v0;
        for (auto fss : params->bound->fract_shore_s) {
            if (fss->v0 > s_max)
                s_max = fss->v0;

            if (fss->v1 > s_max)
                s_max = fss->v1;
        }

        double sigma = rp::get_sigma(s_max, params->data->phys->n_oil, params->data->phys->k_mu);
        p_max = params->bound->pw + (q_max * params->data->l) / (sigma * params->data->rf);
    } else {
        p_max = std::max(params->bound->pc, p_max);
    }

    result_scale->mu0 = params->data->phys->mu_wat;
    result_scale->dp = p_max - params->bound->pw;
    result_scale->perm0 = params->data->perm_res;
    result_scale->poro0 = params->data->poro_fract;
    result_scale->r0 = params->data->rf;
    result_scale->p0 = params->bound->pw;

    // solver data
    auto result_solver_data = std::make_shared<models::SolverData>(
        scale_x(params->data->rw),
        scale_x(params->data->delta),
        params->data->perm_fract / result_scale->perm0,
        params->bound->pc > params->bound->pw);

    result_solver_data->mesh_setts = params->mesh_setts;
    result_solver_data->sat_setts = params->sat_setts;

    result_solver_data->kmu = params->data->phys->k_mu; // mu_wat / mu_oil;
    result_solver_data->l = scale_x(params->data->l);
    result_solver_data->rp_n = params->data->phys->n_oil;
    // result_solver_data->period = params->data->period / result_scale->t0();
    result_solver_data->real_poro = params->data->poro_fract;

    result_solver_data->use_q = params->bound->use_q;
    result_solver_data->fract_end_satur = params->bound->fract_end_satur;
    result_solver_data->fract_end_imperm = params->bound->fract_end_imperm;
    result_solver_data->setFractShoreImperm(params->bound->fract_shore_imperm);
    result_solver_data->fract_shore_s = scale_distr_func(params->bound->fract_shore_s, [&](double s) { return s; });
    result_solver_data->fract_shore_q = scale_distr_func(params->bound->fract_shore_q, scale_q);
    result_solver_data->initial_s = scale_distr_func(params->bound->initial_s, [&](double s) { return s; });
    result_solver_data->fract_end_press = scale_p(params->bound->fract_end_press);
    result_solver_data->pc = scale_p(params->bound->pc);
    result_solver_data->pw = scale_p(params->bound->pw);
    result_solver_data->sw = params->bound->sw;

    return std::make_tuple(result_scale, result_solver_data);
}

}

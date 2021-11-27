#include "dimensionlessService.hpp"

#include "common/models/dataDistribution.hpp"

namespace ble::src::common::services {

std::tuple<std::shared_ptr<models::ScaleData>, std::shared_ptr<models::SolverData>> DimensionlessService::make_dimless(
    const std::shared_ptr<models::InputData> params)
{
    auto result_solver_data = std::make_shared<models::SolverData>();
    auto result_scale = std::make_shared<models::ScaleData>();

    auto scale_x = [&](double x) {
        return x / result_scale->r0;
    };

    auto scale_distr_s = [&](const std::vector<std::shared_ptr<models::DataDistribution>>& data) {
        std::vector<std::shared_ptr<models::DataDistribution>> result;

        for (auto const d : data) {
            auto item = std::make_shared<models::DataDistribution>();
            item->x0 = scale_x(d->x0);
            item->x1 = scale_x(d->x1);
            item->v0 = d->v0;
            item->v1 = d->v1;
            result.push_back(item);
        }

        return result;
    };

    result_scale->mu0 = params->data->phys->mu_wat;
    result_scale->dp = params->bound->pc - params->bound->pw;
    result_scale->perm0 = params->data->perm_res;
    result_scale->poro0 = params->data->poro_fract;
    result_scale->r0 = params->data->r;
    result_scale->p0 = params->bound->pw;

    // solver data
    result_solver_data->mesh_setts = params->mesh_setts;
    result_solver_data->sat_setts = params->sat_setts;

    result_solver_data->delta = scale_x(params->data->delta);
    result_solver_data->fw_lim = params->data->fw_lim;
    result_solver_data->kmu = params->data->phys->mu_wat / params->data->phys->mu_oil;
    result_solver_data->l = scale_x(params->data->l);
    result_solver_data->m = params->data->perm_fract * params->data->delta / (params->data->perm_res * params->data->r);
    result_solver_data->rp_n = params->data->phys->n_oil;
    result_solver_data->rw = scale_x(params->data->rw);
    result_solver_data->use_fwlim = params->data->use_fwlim;
    result_solver_data->period = params->data->period / result_scale->t0();
    result_solver_data->perm_fract = params->data->perm_fract / result_scale->perm0;

    result_solver_data->bound_satur = params->bound->bound_satur;
    result_solver_data->contour_press_bound_type = params->bound->contour_press_bound_type;
    result_solver_data->top_bot_bound_s = scale_distr_s(params->bound->top_bot_bound_s);
    result_solver_data->initial_s = scale_distr_s(params->bound->initial_s);

    return std::make_tuple(result_scale, result_solver_data);
}

}

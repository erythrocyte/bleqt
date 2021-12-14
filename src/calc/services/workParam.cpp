#include "workParam.hpp"

#include <math.h>

#include "common/services/workRp.hpp"
#include "mesh/models/faceType.hpp"

namespace ble::src::calc::services {

double getULiqInject(const std::shared_ptr<mm::Grid> grd, common::models::GridType::TypeEnum grid_type)
{
    double result = 0.;

    for (auto& fc : grd->faces) {
        if (fc->type == mesh::models::FaceType::kContour) {
            result += std::abs(fc->u);
        }
    }

    return result;
}

std::shared_ptr<common::models::WellWorkParams> calc_well_work_param(const std::shared_ptr<mm::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<cm::SolverData> data, double t)
{
    auto result = std::make_shared<common::models::WellWorkParams>();
    result->t = t;
    for (auto& fc : grd->faces) {
        if (fc->type == mm::FaceType::kWell) {
            double ql = -fc->u * fc->area;
            double f = common::services::rp::get_fbl(s[fc->cl1], data->rp_n, data->kmu);
            result->ql += ql;
            result->qw += ql * f;
        }
    }

    result->ql *= 2.0 *data->delta;
    result->qw *= 2.0 *data->delta;

    result->qo = result->ql - result->qw;
    result->fw = result->qw / result->ql * 100.0;

    return result;
}

double calc_q_analytic(const std::shared_ptr<mm::Grid> grd, const std::shared_ptr<cm::SolverData> params)
{
    switch (params->mesh_setts->type) {
    case cm::GridType::kRadial:
        return 2 * M_PI / std::log(1.0 / params->rw);
    case cm::GridType::kRegular:
        return (1.0 - 0.0) / params->get_lenght(); // pc - pw / l
    default:
        return 0.0;
    }
}

} // namespace ble::src
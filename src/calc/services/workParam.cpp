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
    auto calc_fw = [](double qw, double ql) {
        if (std::abs(ql) < 1e-12)
            return 0.0;
        return qw / ql * 100.0;
    };
    auto result = std::make_shared<common::models::WellWorkParams>();
    result->t = t;
    double ql_well, qw_well;
    std::tie(ql_well, qw_well) = get_facetype_ql_qw(grd, data, false, s,
        std::set<mm::FaceType::TypeEnum> { mm::FaceType::kWell });
    result->ql = ql_well;
    result->qw = qw_well;

    double c = 2.0 * data->m; // data->delta * data->perm_fract;
    result->ql *= c;
    result->qw *= c;

    result->qo = result->ql - result->qw;
    result->fw = calc_fw(result->qw, result->ql);

    double ql_shore, qw_shore;
    std::tie(ql_shore, qw_shore) = get_facetype_ql_qw(grd, data, true, s,
        std::set<mm::FaceType::TypeEnum> { mm::FaceType::kTop, mm::FaceType::kBot });
    result->fw_shore = calc_fw(qw_shore, ql_shore);

    return result;
}

double calc_q_analytic(const std::shared_ptr<mm::Grid> grd, const std::shared_ptr<cm::SolverData> params)
{
    switch (params->mesh_setts->type) {
    case cm::GridType::kRadial:
        return 2 * M_PI / std::log(1.0 / params->rw);
    case cm::GridType::kRegular:
        return (1.0 - 0.0) / params->len; // pc - pw / l
    default:
        return 0.0;
    }
}

std::tuple<double, double> get_facetype_ql_qw(const std::shared_ptr<mm::Grid> grd,
    const std::shared_ptr<cm::SolverData> data, bool use_bound_satur,
    const std::vector<double>& s, const std::set<mm::FaceType::TypeEnum>& types)
{
    auto get_s = [&](const std::shared_ptr<mm::Face> fc) {
        return use_bound_satur
            ? fc->bound_satur
            : s[fc->cl1];
    };
    double result_ql = 0.0, result_qw = 0.0;
    for (auto& fc : grd->faces) {
        if (types.find(fc->type) != types.end()) {
            double ql = std::abs(fc->u) * fc->area; // flow is always positive (should be)
            double sat = get_s(fc);
            double f = common::services::rp::get_fbl(sat, data->rp_n, data->kmu);
            result_ql += ql;
            result_qw += ql * f;
        }
    }

    return std::tie(result_ql, result_qw);
}

} // namespace ble::src
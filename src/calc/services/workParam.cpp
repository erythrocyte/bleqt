#include "workParam.hpp"

#include "common/services/workRp.hpp"
#include "mesh/models/faceType.hpp"

namespace ble_src::calc::services {

double getULiqInject(const std::shared_ptr<mm::Grid> grd)
{
    double result = 0.;

    for (auto& fc : grd->faces) {
        if (fc->type == mesh::models::FaceType::kContour) {
            result += fc->u;
        }
    }

    return result;
}

std::shared_ptr<common::models::WellWorkParams> calc_well_work_param(const std::shared_ptr<mm::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::PhysData> data, double t)
{
    auto result = std::make_shared<common::models::WellWorkParams>();
    result->t = t;
    for (auto& fc : grd->faces) {
        if (fc->type == mm::FaceType::kWell) {
            double ql = - fc->u * fc->area;
            double f = common::services::rp::get_fbl(s[fc->cl1], data);
            result->ql += ql;
            result->qw += ql * f;
        }
    }

    result->qo = result->ql - result->qw;
    result->fw = result->qw / result->ql * 100.0;

    return result;
}

} // namespace ble_src
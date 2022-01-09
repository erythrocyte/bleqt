#include "workTimeStep.hpp"

#include <chrono>

#include "common/services/workRp.hpp"
#include "mesh/models/faceType.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

double get_face_dfbl(const std::shared_ptr<mesh::models::Face> fc,
    const std::vector<double>& init, std::shared_ptr<common::models::SolverData> data)
{
    double s2 = (fc->cl2 == -1)
        ? fc->bound_satur
        : init[fc->cl2];
    double s1 = init[fc->cl1];
    double s_av = (s2 + s1) / 2.0;

    double dfbl = std::max(
        std::max(
            cs::rp::get_dfbl(s2, data->rp_n, data->kmu),
            cs::rp::get_dfbl(s1, data->rp_n, data->kmu)),
        cs::rp::get_dfbl(s_av, data->rp_n, data->kmu));

    return dfbl;
}

double get_time_step(const std::shared_ptr<mesh::models::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::SolverData> data)
{
    double result = 1e19;

    std::vector<double> udfbls(grd->cells.size(), 0.);

    for (auto& fc : grd->faces) {
        double dfbl = get_face_dfbl(fc, s, data);
        double udfbl = fc->u * dfbl;
        if (fc->u > 0.) {
            udfbls[fc->cl1] += udfbl;
        } else {
            if (fc->cl2 != -1)
                udfbls[fc->cl2] -= udfbl;
        }
    }

    double cv = data->sat_setts->cur_val;
    for (auto& cl : grd->cells) {
        double udfbl = udfbls[cl->ind];
        double poro = 1.0; // data->data->poro_fract; // for every cell
        if (udfbl > 1e-15) {
            double t = (cv * poro * cl->get_h()) / udfbl;
            if (t > 1e-15 && t < result)
                result = t;
        }
    }

    return result;
}

} // namespace ble::src

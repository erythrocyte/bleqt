#include "workTimeStep.hpp"

#include "common/services/workRp.hpp"

namespace cs = ble_src::common::services;

namespace ble_src {

double get_face_dfbl(const std::shared_ptr<mesh::models::Face> fc,
    const std::vector<double>& init, std::shared_ptr<common::models::PhysData> data)
{
    double s2 = (fc->cl2 == -1)
        ? fc->bound_satur
        : init[fc->cl2];
    double s1 = init[fc->cl1];
    double s_av = (s2 + s1) / 2.0;

    double dfbl = std::max(
        std::max(
            cs::rp::get_dfbl(s2, data),
            cs::rp::get_dfbl(s1, data)),
        cs::rp::get_dfbl(s_av, data));

    return dfbl;
}

double get_time_step(const std::shared_ptr<mesh::models::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::InputData> data)
{
    double result = 1e19;

    std::vector<double> udfbls(grd->cells.size(), 0.);

    for (auto& fc : grd->faces) {
        double dfbl = get_face_dfbl(fc, s, data->phys);
        double udfbl = fc->u * dfbl;
        if (fc->u > 0.) {
            udfbls[fc->cl1] += udfbl;
        } else {
            if (fc->cl2 != -1)
                udfbls[fc->cl2] -= udfbl;
        }
    }

    double cv = data->satSetts->cur_val;
    for (auto& cl : grd->cells) {
        double udfbl = udfbls[cl->ind];
        double poro = data->phys->poro; // for every cell
        if (udfbl > 1e-10) {
            double t = (cv * poro * cl->volume) / udfbl;
            if (t > 1e-8 && t < result)
                result = t;
        }
    }

    return result;
}

} // namespace ble_src

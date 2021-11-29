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
    const std::vector<double>& s, const std::shared_ptr<common::models::SolverData> data,
    std::map<std::string, double>& tt)
{
    double result = 1e19;

    std::vector<double> udfbls(grd->cells.size(), 0.);

    std::chrono::system_clock::time_point start, end;
    std::chrono::system_clock::time_point start2, end2;
    std::chrono::duration<double> diff;

    start = std::chrono::system_clock::now();
    for (auto& fc : grd->faces) {
        start2 = std::chrono::system_clock::now();
        if (fc->u < 0.0 && fc->cl2 == -1) {
            continue;
        }
        end2 = std::chrono::system_clock::now();
        diff = end2 - start2;
        tt["\tcontinue"] += diff.count();

        start2 = std::chrono::system_clock::now();
        double dfbl = get_face_dfbl(fc, s, data);
        end2 = std::chrono::system_clock::now();
        diff = end2 - start2;
        tt["\t get faces dfbl"] += diff.count();

        start2 = std::chrono::system_clock::now();
        double udfbl = fc->u * dfbl;
        if (fc->u > 0.) {
            udfbls[fc->cl1] += udfbl;
        } else {
            udfbls[fc->cl2] -= udfbl;
        }
        end2 = std::chrono::system_clock::now();
        diff = end2 - start2;
        tt["\tadd vector"] += diff.count();
    }
    end = std::chrono::system_clock::now();
    diff = end - start;
    tt["\ttau p1"] += diff.count();

    start = std::chrono::system_clock::now();
    double cv = data->sat_setts->cur_val;
    for (auto& cl : grd->cells) {
        double udfbl = udfbls[cl->ind];
        double poro = 1.0; // data->data->poro_fract; // for every cell
        if (udfbl > 1e-10) {
            double t = (cv * poro * cl->volume) / udfbl;
            if (t > 1e-8 && t < result)
                result = t;
        }
    }
    end = std::chrono::system_clock::now();
    diff = end - start;
    tt["\ttau p2"] += diff.count();

    return result;
}

} // namespace ble::src

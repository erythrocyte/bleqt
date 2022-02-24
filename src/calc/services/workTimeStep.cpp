#include "workTimeStep.hpp"

#include <chrono>
#include <fstream>
#include <math.h>

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

    double cv = data->sat_setts->cv;
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

double get_time_step_new(int index, const std::shared_ptr<mesh::models::Grid> grd,
    const std::vector<double>& s, const std::shared_ptr<common::models::SolverData> data)
{
    std::ofstream f("t_calc.txt", std::ios_base::app);
    f << index << std::endl;
    double result = 1e20;
    std::vector<double> face_q;
    std::vector<double> face_df;
    double cv = data->sat_setts->cv, cg = data->sat_setts->cg;

    for (auto const& fc : grd->faces) {
        double q = fc->u * fc->area;
        double df = get_face_dfbl(fc, s, data);
        face_q.push_back(q);
        face_df.push_back(df);
    }

    for (auto& cl : grd->cells) {
        double sum_qout = 0.0;
        double tg_min = 1e20;
        for (auto const fi : cl->faces) {
            auto fc = grd->faces[fi];
            double q = face_q[fi];
            if ((q < 0 && cl->ind == fc->cl1) || (q > 0 && cl->ind == fc->cl2)) { // out for cl
                sum_qout += std::abs(q);
            } else { // in for cl
                double df = face_df[fi];
                double tg = (cg * cl->volume) / (std::abs(q) * df);
                if (!std::isinf(tg) && tg < tg_min)
                    tg_min = tg;
            }
        }

        double df_v = cs::rp::get_dfbl(s[cl->ind], data->rp_n, data->kmu);
        double tv = (cv * cl->volume) / (df_v * sum_qout);

        double t = std::isinf(tv)
            ? tg_min
            : std::min(tv, tg_min);

        f << "t[cind" << cl->ind << "] = " << t << std::endl;

        if (!std::isinf(t) && t < result)
            result = t;
    }

    f << "==================" << std::endl;
    f << std::endl;

    f.close();

    return result;
}

} // namespace ble::src

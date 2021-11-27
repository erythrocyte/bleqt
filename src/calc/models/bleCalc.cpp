#include "bleCalc.hpp"

#include <fstream>
#include <math.h>
#include <sstream>

#include "calc/services/pressureSolver.hpp"
#include "calc/services/saturSolverAnalytic.hpp"
#include "calc/services/saturSolverNum.hpp"
#include "calc/services/workParam.hpp"
#include "calc/services/workTimeStep.hpp"
#include "common/services/shockFront.hpp"
#include "common/services/workString.hpp"
#include "logging/logger.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::models {

BleCalc::BleCalc()
{
    _results = std::make_shared<BleResultData>();
}

BleCalc::~BleCalc()
{
    _results.reset();
    _wellWorkParams.clear();
    m_tau_data.clear();
}

void BleCalc::calc(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::SolverData> data,
    std::function<void(double)> set_progress)
{
    auto suit_step = [&](double fw, double sum_t) {
        if (data->use_fwlim) {
            return fw <= data->fw_lim;
        } else {
            return sum_t <= data->period;
        }
    };

    auto get_pecr = [&](double fw, double sum_t) {
        double p = data->use_fwlim
            ? fw / data->fw_lim
            : sum_t / data->period;

        return std::min(100.0, p * 100);
    };

    _results->data.clear();
    m_tau_data.clear();
    set_initial_cond(grd, data);
    double sc = cs::shock_front::get_shock_front(data->rp_n, data->kmu);

    int index = 0;
    double sumT = 0.0, sumU = 0.0, cur_fw = 0.0;
    std::vector<double> s_cur, s_prev = _results->data[0]->s;
    std::vector<double> p = _results->data[0]->p;

    services::calc_u(p, s_prev, data, grd);
    int max_index = 100;

    if (!data->sat_setts->need_satur_solve) {
        auto well_params = services::calc_well_work_param(grd, s_prev, data, sumT);
        // double qan = services::calc_q_analytic(grd, data);
        // double qnum = well_params->ql;
        // double perc = std::abs(qan - qnum) / qan * 100.0;

        // std::string mess = common::services::string_format("qan = %.5f, qnum = %.5f, r = %.3f", qan, qnum, perc);
        // logging::write_log(mess, logging::kInfo);

        // save_faces_val(grd, data);
    } else {
        while (suit_step(cur_fw, sumT)) {
            if (index % data->sat_setts->pressure_update_n == 0) {
                p = services::solve_press(grd, s_prev, data);
                services::calc_u(p, s_prev, data, grd);
                // save_press(index, grd, p);
            }

            double t = services::get_time_step(grd, s_prev, data);
            // std::string mess = common::services::string_format("tau = %.8f", t);
            // logging::write_log(mess, logging::kDebug);
            // mess = common::services::string_format("tau after = %.8f", t);
            // logging::write_log(mess, logging::kDebug);

            double u = services::getULiqInject(grd, data->mesh_setts->type);
            // std::string mess = common::services::string_format("uw = %.8f", u);
            // logging::write_log(mess, logging::kInfo);
            sumU += u * t;
            s_cur = services::solve_satur(t, s_prev, data, grd);
            s_prev = s_cur;
            sumT += t;
            m_tau_data.push_back(std::make_shared<common::models::TauData>(sumT, t));

            if (index % data->sat_setts->satur_field_save_n == 0) {
                std::vector<std::tuple<double, double>> xs_an = services::get_satur_exact(sc, sumU, data);
                auto d = std::make_shared<ble::src::common::models::DynamicData>();
                d->t = sumT;
                d->p = p;
                d->s = s_cur;
                d->s_an = xs_an;
                d->p_ex = _results->data[0]->p_ex;

                _results->data.push_back(d);
            }
            index++;

            // double qw = grd->faces[0]->area * grd->faces[0]->u;
            // double qc = grd->faces[0]->area * grd->faces[0]->u;
            // std::string mess = common::services::string_format("qw = %.8f, qc = %.8f", qw, qc);
            // logging::write_log(mess, logging::kInfo);

            auto wwp = services::calc_well_work_param(grd, s_cur, data, sumT);
            cur_fw = wwp->fw;
            _wellWorkParams.push_back(wwp);

            double perc = get_pecr(cur_fw, sumT);
            set_progress(perc);

            // if (index > max_index)
            //     break;
        }

        logging::write_log("saturation solve completed", logging::kInfo);
    }

    m_sum_t = sumT;

    set_progress(100); // completed;
}

void BleCalc::set_initial_cond(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::SolverData> data)
{
    size_t n = grd->cells.size();

    std::vector<double> s(n, 0.);
    std::vector<double> p = services::solve_press(grd, s, data);
    std::vector<double> p_ex = services::calc_press_exact(grd, data);

    auto d = std::make_shared<ble::src::common::models::DynamicData>();
    d->t = 0;
    d->p = p;
    d->s = s;
    d->p_ex = p_ex;

    _results->data.push_back(d);
}

void BleCalc::save_press(int index, const std::shared_ptr<mesh::models::Grid> grd,
    const std::vector<double> p)
{
    std::ostringstream oss;
    oss << "press_" << index << ".dat";
    std::ofstream ofs(oss.str().c_str());

    ofs << "cind\tpress\tum\tup";

    for (auto& cl : grd->cells) {
        ofs << cl->ind << "\t" << p[cl->ind] << "\t" << grd->faces[cl->faces[0]]->u << "\t" << grd->faces[cl->faces[1]]->u << std::endl;
    }

    ofs.close();
}

void BleCalc::save_faces_val(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::SolverData> params)
{
    auto uan = [&](double x) {
        return (1.0 - 0.0) / std::log(1.0 / params->rw) / x;
    };

    std::ofstream f("faces_val.dat");
    for (auto& fc : grd->faces) {
        f << fc->x << "\t" << fc->u << "\t" << fc->area << "\t" << uan(fc->x) << std::endl;
    }
    f.close();
}

void BleCalc::save_any_vector(const std::vector<std::tuple<double, double>>& v, const std::string& fn)
{
    std::ofstream f(fn.c_str());
    double x, y;
    for (auto& item : v) {
        std::tie(x, y) = item;
        f << x << "\t" << y << std::endl;
    }
    f.close();
}

double BleCalc::get_period()
{
    return m_sum_t;
}

}

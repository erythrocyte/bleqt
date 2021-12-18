#include "bleCalc.hpp"

#include <chrono>
#include <fstream>
#include <math.h>
#include <sstream>

#include "calc/services/pressureSolver.hpp"
#include "calc/services/saturAverService.hpp"
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

    m_data = data;
    m_grd = grd;

    _results->data.clear();
    m_tau_data.clear();
    m_fw_data.clear();
    _wellWorkParams.clear();

    m_sum_t = 0.0;
    set_initial_cond();
    double sc = cs::shock_front::get_shock_front(data->rp_n, data->kmu);

    int index = 0;
    double sumT = 0.0, sumU = 0.0, cur_fw = 0.0;

    std::vector<double> s_cur, s_prev = _results->data[0]->s;
    std::vector<double> p = _results->data[0]->p;

    services::calc_u(p, s_prev, data, grd);
    std::chrono::system_clock::time_point start, end;
    std::chrono::duration<double> diff;

    if (!data->sat_setts->need_satur_solve) {
        auto well_params = services::calc_well_work_param(grd, s_prev, data, sumT);

        double q_top_bot = 0.0;
        for (auto& f : grd->faces) {
            if (f->type == mm::FaceType::kTop || f->type == mm::FaceType::kBot) {
                q_top_bot += f->u * f->area;
            }
        }

        // check_conservative();

        // std::cout << "m = " << data->m << ", q = " << well_params->ql << std::endl;
        // double qan = services::calc_q_analytic(grd, data);
        // double qnum = well_params->ql;
        // double perc = std::abs(qan - qnum) / qan * 100.0;

        std::string mess = common::services::string_format("m = %.4f, q = %.5f", data->m, well_params->ql);
        logging::write_log(mess, logging::kInfo);

        // std::string mess = common::services::string_format("m = %.4f, q_well = %.5f, q_top_bot = %.5f", data->m, well_params->ql, q_top_bot);
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

            double u = data->contour_press_bound_type == common::models::BoundCondType::kConst
                ? services::getULiqInject(grd, data->mesh_setts->type)
                : 0.0;
            sumU += u * t;

            s_cur = services::solve_satur(t, s_prev, data, grd);

            s_prev = s_cur;
            sumT += t;
            m_tau_data.push_back(std::make_shared<common::models::TauData>(sumT, t));

            if (index % data->sat_setts->satur_field_save_n == 0) {
                std::vector<std::tuple<double, double>> xs_an;
                if (data->contour_press_bound_type == common::models::BoundCondType::kConst)
                    xs_an = services::get_satur_exact(sc, sumU, data);
                auto d = std::make_shared<ble::src::common::models::DynamicData>();
                d->t = sumT;
                d->p = p;
                d->s = s_cur;
                d->s_an = xs_an;
                d->p_ex = _results->data[0]->p_ex;

                _results->data.push_back(d);
            }
            index++;

            auto wwp = services::calc_well_work_param(grd, s_cur, data, sumT);
            cur_fw = wwp->fw;
            _wellWorkParams.push_back(wwp);
            if (index % 10 == 0)
                std::cout << "fw = " << cur_fw << ", t = " << t << ", index = " << index << std::endl;

            add_aver_fw(sumT, cur_fw, s_cur);

            double perc = get_pecr(cur_fw, sumT);
            set_progress(perc);

            if (index > 5e5)
                break;
        }

        logging::write_log("saturation solve completed", logging::kInfo);
    }

    m_sum_t = sumT;

    set_progress(100); // completed;
}

void BleCalc::set_initial_cond()
{
    size_t n = m_grd->cells.size();

    std::vector<double> s(n, 0.);
    std::vector<double> p = services::solve_press(m_grd, s, m_data);
    std::vector<double> p_ex = services::calc_press_exact(m_grd, m_data);

    auto d = std::make_shared<ble::src::common::models::DynamicData>();
    d->t = 0;
    d->p = p;
    d->s = s;
    d->p_ex = p_ex;

    _results->data.push_back(d);
}

void BleCalc::save_press(int index, const std::vector<double> p)
{
    std::ostringstream oss;
    oss << "press_" << index << ".dat";
    std::ofstream ofs(oss.str().c_str());

    ofs << "cind\tpress\tum\tup";

    for (auto& cl : m_grd->cells) {
        ofs << cl->ind << "\t" << p[cl->ind] << "\t"
            << m_grd->faces[cl->faces[0]]->u << "\t"
            << m_grd->faces[cl->faces[1]]->u << std::endl;
    }

    ofs.close();
}

void BleCalc::save_faces_val()
{
    auto uan = [&](double x) {
        return (1.0 - 0.0) / std::log(1.0 / m_data->rw) / x;
    };

    std::ofstream f("faces_val.dat");
    for (auto& fc : m_grd->faces) {
        f << fc->cntr << "\t" << fc->u << "\t" << fc->area << "\t" << uan(fc->cntr) << std::endl;
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

void BleCalc::add_aver_fw(double t, double fw, const std::vector<double> s)
{
    auto item = std::make_shared<common::models::FwData>();
    item->t = t;
    item->fw_num = fw;
    item->fw_an = 0.0;
    item->sav_an = services::SaturAverService::get_satur_aver_analytic(m_data->rp_n, fw / 100.0, m_data->kmu);
    item->sav_num = services::SaturAverService::get_satur_aver_num(m_grd, s);
    m_fw_data.push_back(item);
}

void BleCalc::check_conservative()
{
    double max_sum_q = -1e6;
    int cind = -1;

    for (auto& cl : m_grd->cells) {
        double sum_q = 0.0;
        for (auto& fi : cl->faces) {
            auto f = m_grd->faces[fi];
            double u = f->cl1 == cl->ind
                ? f->u
                : -f->u;
            double c = mm::FaceType::is_top_bot(f->type)
                ? 2.0 * m_data->m
                : 1.0;
            sum_q += u * f->area / c;
        }

        if (std::abs(sum_q) > max_sum_q) {
            max_sum_q = std::abs(sum_q);
            cind = cl->ind;
        }
    }

    std::string mess = common::services::string_format("residual(%i) = %.12f", cind, max_sum_q);
    logging::write_log(mess, logging::kInfo);
}

}

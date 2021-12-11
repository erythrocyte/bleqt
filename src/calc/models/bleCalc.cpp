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
    m_sum_t = 0.0;
    set_initial_cond();
    double sc = cs::shock_front::get_shock_front(data->rp_n, data->kmu);

    int index = 0;
    double sumT = 0.0, sumU = 0.0, cur_fw = 0.0;
    std::map<std::string, double> speed;
    speed.insert(std::pair<std::string, double>("press", 0.0));
    speed.insert(std::pair<std::string, double>("tau", 0.0));
    speed.insert(std::pair<std::string, double>("u inj", 0.0));
    speed.insert(std::pair<std::string, double>("satur", 0.0));
    speed.insert(std::pair<std::string, double>("fields", 0.0));
    speed.insert(std::pair<std::string, double>("well work", 0.0));

    std::vector<double> s_cur, s_prev = _results->data[0]->s;
    std::vector<double> p = _results->data[0]->p;

    services::calc_u(p, s_prev, data, grd);
    std::chrono::system_clock::time_point start, end;
    std::chrono::duration<double> diff;

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
            start = std::chrono::high_resolution_clock::now();
            if (index % data->sat_setts->pressure_update_n == 0) {
                p = services::solve_press(grd, s_prev, data);
                services::calc_u(p, s_prev, data, grd);
                // save_press(index, grd, p);
            }
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            speed["press"] += diff.count();

            start = std::chrono::high_resolution_clock::now();
            double t = services::get_time_step(grd, s_prev, data, speed);
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            speed["tau"] += diff.count();

            start = std::chrono::high_resolution_clock::now();
            double u = data->contour_press_bound_type == common::models::BoundCondType::kConst
                ? services::getULiqInject(grd, data->mesh_setts->type)
                : 0.0;
            sumU += u * t;
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            speed["u inj"] += diff.count();

            start = std::chrono::high_resolution_clock::now();
            s_cur = services::solve_satur(t, s_prev, data, grd);
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            speed["satur"] += diff.count();

            s_prev = s_cur;
            sumT += t;
            m_tau_data.push_back(std::make_shared<common::models::TauData>(sumT, t));

            start = std::chrono::high_resolution_clock::now();
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
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            speed["fields"] += diff.count();
            index++;

            start = std::chrono::high_resolution_clock::now();
            auto wwp = services::calc_well_work_param(grd, s_cur, data, sumT);
            cur_fw = wwp->fw;
            _wellWorkParams.push_back(wwp);
            end = std::chrono::high_resolution_clock::now();
            diff = end - start;
            speed["well work"] += diff.count();

            add_aver_fw(sumT, cur_fw, s_cur);

            double perc = get_pecr(cur_fw, sumT);
            set_progress(perc);
        }

        logging::write_log("saturation solve completed", logging::kInfo);

        for (auto const& [key, val] : speed) {
            std::string mess = common::services::string_format("%s takes %.5f sec.", key.c_str(), val);
            logging::write_log(mess, logging::kDebug);
        }
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
    item->sav_an = services::SaturAverService::get_satur_aver_analytic(m_data->rp_n, fw / 100.0, m_data->kmu);
    item->sav_num = services::SaturAverService::get_satur_aver_num(m_grd, s);
    m_fw_data.push_back(item);
}

}

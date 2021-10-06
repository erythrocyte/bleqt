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
}

void BleCalc::calc(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::InputData> data,
    std::function<void(double)> set_progress)
{
    _results->data.clear();
    set_initial_cond(grd, data);
    double sc = cs::shock_front::get_shock_front(data->phys);

    int index = 0, pressIndex = 0;
    double sumT = 0.0, sumU = 0.0, saveT = 0.0;
    bool need_save_fiels = false;
    std::vector<double> s_cur, s_prev = _results->data[0]->s;
    std::vector<double> p = _results->data[0]->p;

    services::calc_u(p, s_prev, data, grd);

    if (!data->satSetts->need_satur_solve) {
        auto well_params = services::calc_well_work_param(grd, s_prev, data->phys, sumT);
        double qan = services::calc_q_analytic(grd, data);
        double qnum = well_params->ql;
        double perc = std::abs(qan - qnum) / qan * 100.0;

        std::string mess = common::services::string_format("qan = %.5f, qnum = %.5f, r = %.3f", qan, qnum, perc);
        logging::write_log(mess, logging::kInfo);

        save_faces_val(grd, data);
    } else {
        while (sumT < data->model->period) {
            if (pressIndex == 0 || pressIndex == data->satSetts->pN) {
                p = services::solve_press(grd, s_prev, data);
                services::calc_u(p, s_prev, data, grd);
                //save_press(index, grd, p);
                pressIndex = 0;
            }
            pressIndex++;

            double t = services::get_time_step(grd, s_prev, data);
            // std::string mess = common::services::string_format("tau = %.8f", t);
            // logging::write_log(mess, logging::kInfo);
            if (saveT + t >= data->model->save_field_step) {
                t = data->model->save_field_step - saveT;
                saveT = 0.0;
                need_save_fiels = true;
            } else {
                saveT += t;
                need_save_fiels = false;
            }

            double u = services::getULiqInject(grd, data->grd->type);
            // std::string mess = common::services::string_format("uw = %.8f", u);
            // logging::write_log(mess, logging::kInfo);
            sumU += u * t;
            s_cur = services::solve_satur(t, s_prev, data, grd);
            s_prev = s_cur;
            sumT += t;

            if (need_save_fiels) {
                std::vector<std::tuple<double, double>> xs_an = services::get_satur_exact(sc, sumU, data);
                auto d = std::make_shared<ble::src::common::models::DynamicData>();
                d->t = sumT;
                d->p = p;
                d->s = s_cur;
                d->s_an = xs_an;
                d->p_ex = _results->data[0]->p_ex;

                _results->data.push_back(d);
                index++;
            }

            auto wwp = services::calc_well_work_param(grd, s_cur, data->phys, sumT);
            _wellWorkParams.push_back(wwp);

            double perc = std::min(100.0, (sumT / data->model->period * 100.0));
            set_progress(perc);
        }

        logging::write_log("saturation solve completed", logging::kInfo);
    }

    set_progress(100); // completed;
}

void BleCalc::set_initial_cond(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::InputData> data)
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
    const std::shared_ptr<common::models::InputData> data)
{
    auto uan = [&](double x) {
        return (1.0 - 0.0) / std::log(data->grd->rc / data->grd->rw) / x;
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

}

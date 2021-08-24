#include "bleCalc.hpp"

#include <fstream>
#include <sstream>

#include "calc/services/pressureSolver.hpp"
#include "calc/services/saturSolverAnalytic.hpp"
#include "calc/services/saturSolverNum.hpp"
#include "calc/services/workParam.hpp"
#include "calc/services/workTimeStep.hpp"
#include "common/services/shockFront.hpp"

namespace cs = ble_src::common::services;

namespace ble_src::calc::models {

BleCalc::BleCalc()
{
    _results = std::make_shared<BleResultData>();
}

BleCalc::~BleCalc()
{
    _results.reset();
}

void BleCalc::calc(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::InputData> data,
    std::function<void(double)> set_progress)
{
    _results->data.clear();
    set_initial_cond(grd->cells.size());
    double sc = cs::shock_front::get_shock_front(data->phys);

    int index = 0, pressIndex = 0;
    double sumT = 0.0, sumU = 0.0, saveT = 0.0;
    bool need_save_fiels = false;
    std::vector<double> s_cur, s_prev = _results->data[0]->s;
    std::vector<double> p = _results->data[0]->p;
    while (sumT < data->model->period) {
        if (pressIndex == 0 || pressIndex == data->satSetts->pN) {
            p = services::solve_press(grd, s_prev, data->phys);
            services::calc_u(p, s_prev, data->phys, grd);
            //save_press(index, grd, p);
            pressIndex = 0;
        }
        pressIndex++;

        double t = services::get_time_step(grd, s_prev, data);
        if (saveT + t >= data->model->save_field_step) {
            t = data->model->save_field_step - saveT;
            saveT = 0.0;
            need_save_fiels = true;
        } else {
            saveT += t;
            need_save_fiels = false;
        }

        sumU += services::getULiqInject(grd) * t;
        s_cur = services::solve_satur(t, s_prev, data, grd);
        s_prev = s_cur;
        sumT += t;

        if (need_save_fiels) {
            std::vector<std::tuple<double, double>> xs_an = services::get_satur_exact(sc, sumU, data);
            auto d = std::make_shared<ble_src::common::models::DynamicData>();
            d->t = sumT;
            d->p = p;
            d->s = s_cur;
            d->s_an = xs_an;

            _results->data.push_back(d);
            index++;
        }

        double perc = std::min(100.0, (sumT / data->model->period * 100.0));
        set_progress(perc);
    }

    set_progress(100); // completed;
}

void BleCalc::set_initial_cond(size_t n)
{
    std::vector<double> s(n, 0.);
    std::vector<double> p(n, 1.);

    auto d = std::make_shared<ble_src::common::models::DynamicData>();
    d->t = 0;
    d->p = p;
    d->s = s;

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
}

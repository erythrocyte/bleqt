#include "bleCalc.hpp"

#include "shockFront.hpp"
#include "workTimeStep.hpp"
#include "workParam.hpp"
#include "saturSolverAnalytic.hpp"
#include "saturSolverNum.hpp"
#include "pressureSolver.hpp"

ble_src::BleCalc::BleCalc()
{
    _results = std::make_shared<BleResultData>();
}

ble_src::BleCalc::~BleCalc()
{
    _results.reset();
}

void ble_src::BleCalc::calc(const std::shared_ptr<Grid> grd,
                            const std::shared_ptr<InputData> data,
                            std::function<void(double)> set_progress)
{
    _results->data.clear();
    set_initial_cond(grd->cells.size());
    double sc = ble_src::get_shock_front(data->phys);

    int index = 1;
    int pressIndex = 0;
    double sumT = 0.;
    double sumU = 0.;
    while (sumT < data->model->period)
    {
        std::vector<double> s_prev = _results->data[index - 1]->s;

        std::vector<double> p = _results->data[index - 1]->p;
        if (pressIndex == 0 || pressIndex == data->satSetts->pN)
        {
            p = solve_press(grd, s_prev, data->phys);
            calc_u(p, s_prev, data->phys, grd);
            pressIndex = 0;
        }
        pressIndex++;

        double t = ble_src::get_time_step(grd, s_prev, data);

        sumU += ble_src::getULiqInject(grd) * t;
        std::vector<std::tuple<double, double>> xs_an = ble_src::get_satur_exact(sc, sumU, data);

        std::vector<double> s = solve_satur(t, s_prev, data, grd);
        sumT += t;

        std::shared_ptr<ble_src::DynamicData> d(new ble_src::DynamicData());
        d->t = sumT;
        d->p = p;
        d->s = s;
        d->s_an = xs_an;

        _results->data.push_back(d);
        index++;

        double perc = std::min(100.0, (sumT / data->model->period * 100.0));
        set_progress(perc);
    }

    set_progress(100); // completed;
}

void ble_src::BleCalc::set_initial_cond(size_t n)
{
    std::vector<double> s(n, 0.);
    std::vector<double> p(n, 1.);

    std::shared_ptr<ble_src::DynamicData> d(new ble_src::DynamicData());
    d->t = 0;
    d->p = p;
    d->s = s;

    _results->data.push_back(d);
}

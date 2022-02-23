#include "voids.hpp"

#include <iostream>
#include <vector>

#include "calc/models/bleCalc.hpp"
#include "calc/models/saturSolverSettings.hpp"
#include "calc/models/saturSolverType.hpp"
#include "common/models/boundCondType.hpp"
#include "common/models/dataDistribution.hpp"
#include "common/models/gridType.hpp"
#include "common/models/meshSettings.hpp"
#include "mesh/services/makeGrid.hpp"

namespace mss = ble::src::mesh::services;
namespace clm = ble::src::calc::models;

namespace ble::bin {

std::shared_ptr<cm::SolverData> Calculator::get_solver_data()
{
    auto result = std::make_shared<cm::SolverData>(
        0.01 / 100, // rw
        0.005 / 100.0, // delta
        10 // perm_fract
    );

    // mesh settings
    result->mesh_setts = std::make_shared<cm::MeshSettings>();
    result->mesh_setts->n = 500;
    result->mesh_setts->type = cm::GridType::kRadial;

    // satur solver settings
    result->sat_setts = std::make_shared<clm::SaturSolverSetts>();
    result->sat_setts->cv = 0.5e-6;
    result->sat_setts->cg = 0.9;
    result->sat_setts->need_satur_solve = true;
    result->sat_setts->pressure_update_n = 10;
    result->sat_setts->satur_field_save_n = 1e7;
    result->sat_setts->type = clm::SaturSolverType::kImplicit;
    result->sat_setts->max_iter = 2.5e7;
    result->sat_setts->use_fw_delta = false;
    result->sat_setts->fw_delta = 1e-5;
    result->sat_setts->fw_delta_iter = 1e4;
    result->sat_setts->use_fw_shorewell_converge = true;
    result->sat_setts->fw_shw_conv = 3; // %

    // result->delta = 0.005 / 100.0;
    result->fw_lim = 99;
    result->kmu = 1.0;
    result->l = 500.0 / 100.0;
    // result->m = 10.0;
    result->rp_n = 2.0;
    // result->rw = 0.01 / 100;
    result->use_fwlim = true;
    result->period = 1.0;
    // result->perm_fract = 10;
    result->bound_satur = 1.0;
    result->contour_press_bound_type = cm::BoundCondType::kImpermeable;
    result->real_poro = 0.2;

    auto item = std::make_shared<cm::DataDistribution>();
    item->v0 = 0.0;
    item->v1 = 0.0;
    item->x0 = 0.0;
    item->x1 = 1.0;
    result->initial_s.push_back(item);

    return result;
}

std::shared_ptr<msm::Grid> Calculator::get_grid(const std::shared_ptr<cm::SolverData> params)
{
    return mss::make_grid(params);
}

void Calculator::solve(const std::shared_ptr<cm::SolverData> params, const std::shared_ptr<msm::Grid> grd)
{
    print_index = 0;
    auto solver = std::make_shared<clm::BleCalc>();
    std::function<void(int)> a = std::bind(&Calculator::update_progress, this, std::placeholders::_1);
    solver->calc(grd, params, a, false);

    auto wwp = solver->get_well_work_params();

    std::cout << "last fw = " << wwp[wwp.size() - 1]->fw << std::endl;
    print_index = 0;
    update_progress(100);
}

void Calculator::update_progress(double perc)
{
    if (print_index % PRINT_STEP == 0) {
        std::cout << "calc progress: " << perc << " %" << std::endl;
    }

    print_index++;
}

void Calculator::run_s_const_loop()
{
    std::vector<double> ms = { /*1e-1, 1e0, */ 1e2, /*1e2, 1e3*/ };
    std::vector<double> scs = { 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0 };
    // std::vector<double> scs = {0.85 };

    for (auto const& mi : ms) {
        for (auto const& s : scs) {
            auto data = get_solver_data();
            data->perm_fract = mi / data->delta;

            auto item = std::make_shared<cm::DataDistribution>();
            item->v0 = s;
            item->v1 = s;
            item->x0 = 0.0;
            item->x1 = 1.0;
            data->top_bot_bound_s.push_back(item);

            auto grd = get_grid(data);
            solve(data, grd);
        }
    }
}

}

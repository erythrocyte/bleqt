#include "calculator.hpp"

#include <iostream>
#include <vector>

#include "fwWellShoreConvResultsSaver.hpp"
#include "models/fwWellShoreConvResults.hpp"
#include "models/oneFwWellShoreConvData.hpp"
#include "solverDataPreparer.hpp"

#include "calc/models/bleCalc.hpp"
#include "calc/models/saturSolverSettings.hpp"
#include "calc/models/saturSolverType.hpp"
#include "common/models/dataDistribution.hpp"
#include "common/models/gridType.hpp"
#include "common/models/meshSettings.hpp"
#include "common/models/timeStepType.hpp"
#include "common/services/shockFront.hpp"
#include "common/services/workDir.hpp"
#include "common/services/workRp.hpp"
#include "file/services/workFile.hpp"
#include "mesh/services/makeGrid.hpp"

namespace mss = ble::src::mesh::services;
namespace clm = ble::src::calc::models;
namespace cm = ble::src::common::models;
namespace cs = ble::src::common::services;
namespace fss = ble::src::file::services;

namespace ble::bin::services {

std::shared_ptr<msm::Grid> Calculator::get_grid(const std::shared_ptr<cm::SolverData> params)
{
    return mss::make_grid(params);
}

std::shared_ptr<clm::BleResultData> Calculator::solve(const std::shared_ptr<cm::SolverData> params, const std::shared_ptr<msm::Grid> grd)
{
    print_index = 0;
    auto solver = std::make_shared<clm::BleCalc>();
    std::function<void(int)> a = std::bind(&Calculator::update_progress, this, std::placeholders::_1);
    solver->calc(grd, params, a, false);

    // std::cout << "last fw = " << wwp[wwp.size() - 1]->fw << std::endl;
    print_index = 0;
    update_progress(100);

    auto result = std::make_shared<clm::BleResultData>(*solver->get_result());
    // auto result = solver->get_result();
    return result;
}

void Calculator::update_progress(double perc)
{
    if (print_index % PRINT_STEP == 0) {
        // std::cout << "calc progress: " << perc << " %" << std::endl;
    }

    print_index++;
}

void Calculator::run_s_const_loop()
{
    if (fss::file_exists("dd.dat")) {
        std::remove("dd.dat");
    }

    // if (fss::file_exists("1.dat")) {
    //     std::remove("1.dat");
    // }

    if (fss::file_exists("aver.dat")) {
        std::remove("aver.dat");
    }

    // std::vector<double> ms = { 1e-1, 1e0, 1e1, 1e2, 1e3 };
    // std::vector<double> scs = { 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1.0 };
    std::vector<double> scs = { 0.35 };
    std::vector<double> ms = { 1e3 };

    for (auto const& mi : ms) {
        for (auto const& s : scs) {
            auto data = SolverDataPreparer::get_solver_data();
            data->setPermFract(mi / data->delta);
            std::cout << "kf = " << data->getPermFract() << "\n";
            std::cout << "delt = " << data->delta << "\n";
            std::cout << "sb = " << s << "\n";

            auto item = std::make_shared<cm::DataDistribution>();
            item->v0 = s;
            item->v1 = s;
            item->x0 = 0.0;
            item->x1 = 1.0;
            data->fract_shore_s.push_back(item);

            auto grd = get_grid(data);
            solve(data, grd);
        }
    }
}

void Calculator::run_linear()
{
    int n = 20;
    double fw0 = 99, fw1 = 99, dfw = (fw1 - fw0) / (n - 1);

    auto data = SolverDataPreparer::get_linear_solver_data();
    data->fract_end_satur = 1.0;
    auto grd = get_grid(data);
    auto sc = cs::shock_front::get_shock_front(data->rp_n, data->kmu);
    fw0 = cs::rp::get_fbl(sc, data->rp_n, data->kmu) * 100;
    dfw = (fw1 - fw0) / (n - 1);

    std::vector<double> ns = { 1e2 };

    for (auto const& ni : ns) {
        data->mesh_setts->n = ni;
        std::cout << "n = " << ni << "\n";
        auto grd = get_grid(data);

        for (int k = 0; k < n; k++) {
            data->sat_setts->fw_lim = fw0 + k * dfw;
            solve(data, grd);
        }

        break;
    }
}

void Calculator::run_pv_m()
{
    auto data = SolverDataPreparer::get_solver_data();
    data->kmu = 1.0;
    data->rp_n = 2.0;
    data->sat_setts->use_fw_shorewell_converge = true;
    data->sat_setts->use_fwlim = false;

    // prepare shore saturation;
    double sc = cs::shock_front::get_shock_front(data->rp_n, data->kmu);
    auto item = std::make_shared<cm::DataDistribution>();
    item->v0 = sc;
    item->v1 = sc;
    item->x0 = 0.8;
    item->x1 = 1.0;
    data->fract_shore_s.push_back(item);

    // prepare input dynamic data;
    std::vector<double> ms = { 1e-2, 2e-2, 4e-2, 6e-2, 8e-2, 1e-1, 5e-1, 1e0, 1e1, 1e2 };
    std::vector<double> taus = { 1e-5, 1e-5, 1e-5, 1e-5, 1e-5, 1e-6, 1e-6, 1e-7, 1e-7, 1e-7 };
    std::vector<double> fw_deltas = { 1, 10 };

    // std::vector<std::shared_ptr<models::FwWellShoreConvResults>> results;

    std::string dir_path = "out/m_pv";
    cs::work_dir::remove_dir_my(dir_path);
    cs::work_dir::make_dir_my(dir_path);

    for (auto const& fw_delta : fw_deltas) {
        auto one_result = std::make_shared<models::FwWellShoreConvResults>();
        one_result->fw_conv_delta = fw_delta;
        data->sat_setts->fw_shore_well_conv_delta = fw_delta;
        int index = 0;

        for (auto const& mi : ms) {
            data->setPermFract(mi / data->delta);
            data->sat_setts->tau = taus[index];

            auto grd = get_grid(data);
            auto solve_result = solve(data, grd);

            auto last_aver = solve_result->aver.back();

            auto one_data = std::make_shared<models::OneFwWellShoreConvData>();
            one_data->m = mi;
            one_data->pv = last_aver->pv;
            one_result->data.push_back(one_data);

            index++;
        }

        // results.push_back(one_result);

        // save to file;
        FwWellShoreConvResultsSaver::save(dir_path, one_result);
    }
}

}

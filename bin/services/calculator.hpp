#ifndef BLE_BIN_SERVICES_CALCULATOR_H
#define BLE_BIN_SERVICES_CALCULATOR_H

#include <iostream>
#include <memory>

#include "calc/models/bleResultData.hpp"
#include "common/models/solverData.hpp"
#include "mesh/models/grid.hpp"

namespace cm = ble::src::common::models;
namespace msm = ble::src::mesh::models;
namespace clm = ble::src::calc::models;

namespace ble::bin::services {

class Calculator {

public:
    Calculator() { }
    ~Calculator() { }
    void run_s_const_loop();
    void run_linear();
    void run_pv_m();

private:
    int const PRINT_STEP = 1000;
    int print_index = 0;

    void update_progress(double perc);    
    std::shared_ptr<msm::Grid> get_grid(const std::shared_ptr<cm::SolverData> params);
    std::shared_ptr<clm::BleResultData> solve(const std::shared_ptr<cm::SolverData> params,
        const std::shared_ptr<msm::Grid> grd);
};

}

#endif
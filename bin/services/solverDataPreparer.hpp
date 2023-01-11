#ifndef BLE_BIN_SERVICES_SOLVERDATAPREPARER_H
#define BLE_BIN_SERVICES_SOLVERDATAPREPARER_H

#include <iostream>
#include <memory>

#include "common/models/solverData.hpp"

namespace cm = ble::src::common::models;

namespace ble::bin::services {

class SolverDataPreparer {
public:
    static std::shared_ptr<cm::SolverData> get_linear_solver_data();
    static std::shared_ptr<cm::SolverData> get_solver_data();

private:
    SolverDataPreparer() { }
    ~SolverDataPreparer() { }
};

}

#endif

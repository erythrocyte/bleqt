#ifndef BLE_SRC_CALC_MODELS_SUITSTEPDTO_H_
#define BLE_SRC_CALC_MODELS_SUITSTEPDTO_H_

#include <iostream>
#include <memory>

#include "common/models/solverData.hpp"
#include "common/models/wellWorkParams.hpp"

namespace ble::src::calc::models {

class SuitStepDto {
public:
    SuitStepDto() { }
    ~SuitStepDto() { }

    double sum_t;
    int index;
    double scur0;
    double prev_fw;
    int fw_const_iter;
    double tau;

    std::shared_ptr<common::models::WellWorkParams> wwp;
    std::shared_ptr<common::models::SolverData> data;
};
}

#endif
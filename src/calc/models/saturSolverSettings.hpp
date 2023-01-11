#ifndef BLE_SRC_CALC_MODELS_SATURSOLVERSETTINGS_H_
#define BLE_SRC_CALC_MODELS_SATURSOLVERSETTINGS_H_

#include "common/models/timeStepType.hpp"
#include "saturSolverType.hpp"

namespace scm = ble::src::common::models;

namespace ble::src::calc::models {

class SaturSolverSetts {
public:
    double cv;
    double cg;
    int pressure_update_n;
    SaturSolverType::TypeEnum type;
    bool need_satur_solve;
    int satur_field_save_n;
    int max_iter;

    bool use_fw_delta;
    double fw_delta;
    int fw_delta_iter;

    double tau;
    int simple_iter_count;
    bool use_fw_shorewell_converge;
    double fw_shore_well_conv_delta;

    double fw_lim;
    bool use_fwlim;

    scm::TimeStepType::TypeEnum time_step_type;
};

}

#endif

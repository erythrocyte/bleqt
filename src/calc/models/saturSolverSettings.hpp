#ifndef BLE_SRC_CALC_MODELS_SATURSOLVERSETTINGS_H_
#define BLE_SRC_CALC_MODELS_SATURSOLVERSETTINGS_H_

#include "saturSolverType.hpp"

namespace ble::src::calc::models {

class SaturSolverSetts {
public:
    double cur_val;
    int pressure_update_n;
    SaturSolverType::TypeEnum type;
    bool need_satur_solve;
    int satur_field_save_n;
};

}

#endif

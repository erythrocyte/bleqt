#ifndef BLE_SRC_COMMON_MODELS_SOLVERDATA_H_
#define BLE_SRC_COMMON_MODELS_SOLVERDATA_H_

#include <iostream>
#include <memory>

#include "boundCondData.hpp"
#include "boundCondType.hpp"
#include "calc/models/saturSolverSettings.hpp"
#include "dataDistribution.hpp"
#include "meshSettings.hpp"

namespace ble::src::common::models {

class SolverData {
public:
    SolverData(double rw, double delta, double perm_fract);

    int rp_n;
    double kmu;
    double perm_fract; // TODO : make const;
    double l; // distance in reservoir;
    double rw; // TODO : make const;
    double delta; // TODO : make const;
    double period;
    double fw_lim;
    bool use_fwlim;
    // double get_lenght() { return 1.0 - rw; }
    // double get_m() { return delta * perm_fract; }
    double real_poro;
    double m;
    double len;

    std::vector<std::shared_ptr<DataDistribution>> top_bot_bound_s;
    std::vector<std::shared_ptr<DataDistribution>> initial_s;
    BoundCondType::TypeEnum contour_press_bound_type;
    double bound_satur;

    std::shared_ptr<MeshSettings> mesh_setts = std::make_shared<MeshSettings>();
    std::shared_ptr<calc::models::SaturSolverSetts> sat_setts = std::make_shared<calc::models::SaturSolverSetts>();

    void update_perm_fract(double kf);
};

}

#endif

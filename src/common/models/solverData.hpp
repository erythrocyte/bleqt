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
    SolverData(double rw, double delta, double perm_fract, bool is_producer);

    int rp_n;
    double kmu;
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
    double eps;

    std::vector<std::shared_ptr<DataDistribution>> top_bot_bound_s;
    std::vector<std::shared_ptr<DataDistribution>> initial_s;
    // BoundCondType::TypeEnum contour_press_bound_type;
    double bound_satur;

    std::shared_ptr<MeshSettings> mesh_setts = std::make_shared<MeshSettings>();
    std::shared_ptr<calc::models::SaturSolverSetts> sat_setts = std::make_shared<calc::models::SaturSolverSetts>();

    void set_perm_fract(double kf);
    double get_perm_fract();

    void set_contour_press_bound_type(BoundCondType::TypeEnum value);
    BoundCondType::TypeEnum get_contour_press_bound_type();

    bool is_producer_well();

private:
    double pw; // well press
    double pc; // reservoir contour press
    bool is_producer;
    double m_kf;
    BoundCondType::TypeEnum m_contour_press_bound_type;

    void update_eps();
};

}

#endif

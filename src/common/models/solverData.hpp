#ifndef BLE_SRC_COMMON_MODELS_SOLVERDATA_H_
#define BLE_SRC_COMMON_MODELS_SOLVERDATA_H_

#include <iostream>
#include <memory>

#include "boundCondData.hpp"
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
    // double period;
    // double get_lenght() { return 1.0 - rw; }
    // double get_m() { return delta * perm_fract; }
    double real_poro;
    double m;
    double len;
    double eps;

    double pw; // well press
    double pc; // reservoir contour press
    double fract_end_press;

    std::vector<std::shared_ptr<DataDistribution>> initial_s;
    double fract_end_satur;
    double sw; // satur well
    std::vector<std::shared_ptr<DataDistribution>> fract_shore_s;
    std::vector<std::shared_ptr<DataDistribution>> fract_shore_q;

    bool use_q;
    bool fract_end_imperm;

    std::shared_ptr<MeshSettings> mesh_setts = std::make_shared<MeshSettings>();
    std::shared_ptr<calc::models::SaturSolverSetts> sat_setts = std::make_shared<calc::models::SaturSolverSetts>();

    void setPermFract(double kf);
    double getPermFract();

    void setFractShoreImperm(bool value);
    bool isFractShoreImperm();

    bool is_producer_well();

private:
    bool is_producer;
    double m_kf;
    bool m_is_fract_shore_imperm;

    void update_eps();
};

}

#endif

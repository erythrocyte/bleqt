#include "solverDataPreparer.hpp"

namespace clm = ble::src::calc::models;

namespace ble::bin::services {
std::shared_ptr<cm::SolverData> SolverDataPreparer::get_linear_solver_data()
{
    auto result = std::make_shared<cm::SolverData>(
        0.01, // rw
        0.5, // delta -- no fract
        100, // perm_fract,
        true);

    // mesh settings
    result->mesh_setts = std::make_shared<cm::MeshSettings>();
    result->mesh_setts->n = 200;
    result->mesh_setts->type = cm::GridType::kRegular;

    // satur solver settings
    result->sat_setts = std::make_shared<clm::SaturSolverSetts>();
    result->sat_setts->need_satur_solve = true;
    result->sat_setts->pressure_update_n = 10;
    result->sat_setts->satur_field_save_n = 1e7;
    result->sat_setts->type = clm::SaturSolverType::kImplicit;
    result->sat_setts->max_iter = 2.5e7;
    result->sat_setts->use_fw_delta = false;
    result->sat_setts->fw_delta = 1e-5;
    result->sat_setts->fw_delta_iter = 1e6;
    result->sat_setts->use_fw_shorewell_converge = true;
    result->sat_setts->fw_shore_well_conv_delta = 5; // %
    result->sat_setts->time_step_type = cm::TimeStepType::kOld;
    result->sat_setts->tau = 1e-3;
    result->sat_setts->simple_iter_count = 3;
    result->sat_setts->fw_lim = 70;
    result->sat_setts->use_fwlim = true;

    result->kmu = 1.0;
    result->l = 5;
    result->rp_n = 3.0;

    // result->period = 1.0;
    result->fract_end_satur = 1.0;
    result->fract_end_imperm = false;
    result->setFractShoreImperm(true);
    result->real_poro = 0.2;

    auto item = std::make_shared<cm::DataDistribution>();
    item->v0 = 0.0;
    item->v1 = 0.0;
    item->x0 = 0.0;
    item->x1 = 1.0;
    result->initial_s.push_back(item);

    return result;
}

std::shared_ptr<cm::SolverData> SolverDataPreparer::get_solver_data()
{
    double rf = 100.0; // m
    auto result = std::make_shared<cm::SolverData>(
        0.01 / rf, // rw
        0.001 / rf, // delta
        10, // perm_fract
        true);

    result->pw = 0.0;
    result->pc = 1.0;

    // mesh settings
    result->mesh_setts = std::make_shared<cm::MeshSettings>();
    result->mesh_setts->n = 200;
    result->mesh_setts->type = cm::GridType::kRadial;

    // satur solver settings
    result->sat_setts = std::make_shared<clm::SaturSolverSetts>();
    result->sat_setts->cv = 1e-1;
    result->sat_setts->cg = result->sat_setts->cv;
    result->sat_setts->need_satur_solve = true;
    result->sat_setts->pressure_update_n = 10;
    result->sat_setts->satur_field_save_n = 1e7;
    result->sat_setts->type = clm::SaturSolverType::kImplicit;
    result->sat_setts->max_iter = 1e8;
    result->sat_setts->use_fw_delta = false;
    result->sat_setts->fw_delta = 1e-5;
    result->sat_setts->fw_delta_iter = 1e6;
    result->sat_setts->use_fw_shorewell_converge = true;
    result->sat_setts->fw_shore_well_conv_delta = 1; // %
    result->sat_setts->time_step_type = cm::TimeStepType::kNew;

    result->sat_setts->tau = 1e-5;
    result->sat_setts->simple_iter_count = 3;
    result->sat_setts->fw_lim = 70;
    result->sat_setts->use_fwlim = false;

    result->kmu = 1.0;
    result->l = 500.0 / rf;
    result->rp_n = 3.0;

    // result->period = 2e3;
    result->fract_end_satur = 1.0;
    result->fract_end_imperm = true;
    result->setFractShoreImperm(false);
    result->real_poro = 0.2;
    result->use_q = false;

    auto item = std::make_shared<cm::DataDistribution>();
    item->v0 = 0.0;
    item->v1 = 0.0;
    item->x0 = 0.0;
    item->x1 = 1.0;
    result->initial_s.push_back(item);

    // item = std::make_shared<cm::DataDistribution>();
    // item->v0 = 1.0;
    // item->v1 = 1.0;
    // item->x0 = 0.0;
    // item->x1 = result->len + result->rw;
    // result->top_bot_bound_s.push_back(item);

    return result;
}

}

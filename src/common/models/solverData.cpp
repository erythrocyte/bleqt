#include "solverData.hpp"

namespace ble::src::common::models {

SolverData::SolverData(double rw, double delta, double perm_fract, bool is_producer)
{
    this->rw = rw;
    this->delta = delta;
    this->m_kf = perm_fract;

    this->len = 1.0 - rw;
    this->m = delta * perm_fract;

    this->is_producer = is_producer;
}

bool SolverData::is_producer_well()
{
    return this->is_producer;
}

void SolverData::set_perm_fract(double kf)
{
    this->m_kf = kf;
    this->m = this->delta * this->m_kf;
    update_eps();
}

double SolverData::get_perm_fract()
{
    return this->m_kf;
}

void SolverData::set_contour_press_bound_type(BoundCondType::TypeEnum value)
{
    this->m_contour_press_bound_type = value;
    update_eps();
}

BoundCondType::TypeEnum SolverData::get_contour_press_bound_type()
{
    return this->m_contour_press_bound_type;
}

void SolverData::update_eps()
{
    switch (this->m_contour_press_bound_type) {
    case common::models::BoundCondType::kImpermeable: {
        this->eps = 1.0 / m_kf;
        break;
    }
    case common::models::BoundCondType::kConst: // coz only one k is exists and dimless = 1.0;
    default:
        this->eps = 1.0;
        break;
    }
}

}

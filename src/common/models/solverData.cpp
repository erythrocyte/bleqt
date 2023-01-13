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

void SolverData::setPermFract(double kf)
{
    this->m_kf = kf;
    this->m = this->delta * this->m_kf;
    update_eps();
}

double SolverData::getPermFract()
{
    return this->m_kf;
}

void SolverData::setFractShoreImperm(bool value)
{
    this->m_is_fract_shore_imperm = value;
    update_eps();
}

bool SolverData::isFractShoreImperm()
{
    return this->m_is_fract_shore_imperm;
}

void SolverData::update_eps()
{
    double value = use_q ? 1.0 : 1.0 / m_kf;
    this->eps = m_is_fract_shore_imperm ? 1.0 : value;
}
}

#include "solverData.hpp"

namespace ble::src::common::models {

SolverData::SolverData(double rw, double delta, double perm_fract)
{
    this->rw = rw;
    this->delta = delta;
    this->perm_fract = perm_fract;

    this->len = 1.0 - rw;
    this->m = delta * perm_fract;
}

void SolverData::update_perm_fract(double kf)
{
    this->perm_fract = kf;
    this->m = this->delta * this->perm_fract;
}

}

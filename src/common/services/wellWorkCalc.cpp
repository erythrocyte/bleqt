#include "wellWorkCalc.hpp"

#include <cmath>
#include <iostream>

namespace ble::src::common::services::wellworkcalc {

double calc_fw(double ql, double qw)
{
    if (std::abs(ql) < 1e-12)
        return 0.0;
    return qw / ql * 100.0;
}

double calc_qw(double ql, double fw)
{
    return ql * (fw / 100.0);
}

double calc_qo(double ql, double fw)
{
    double qw = calc_qw(ql, fw);
    return ql - qw;
}
}
#include "workRp.hpp"

#include <cmath>

namespace ble::src::common::services::rp {

double get_kw(double s, double n)
{
    return std::pow(s, n);
}

double get_koil(double s, double n)
{
    return std::pow((1. - s), n);
}

double get_sigma(double s, double n, double kmu)
{
    return get_kw(s, n) + kmu * get_koil(s, n);
}

double get_fbl(double s, double n, double kmu)
{
    double kw = get_kw(s, n);
    double sig = get_sigma(s, n, kmu);

    return kw / sig;
}

double get_dfbl(double s, double n, double kmu)
{
    double kw = get_kw(s, n);
    double dkw = n * std::pow(s, n - 1), dkoil = -n * std::pow((1 - s), n - 1);

    double f = get_sigma(s, n, kmu);
    double f2 = f * f;
    double ff = dkw + kmu * dkoil;

    return (dkw * f - ff * kw) / f2;
}

}

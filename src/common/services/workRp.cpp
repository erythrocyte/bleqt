#include "workRp.hpp"

#include <cmath>

namespace ble::src::common::services::rp {

double my_pow(double val, int degree)
{
    double ans = 1;
    for (int k = 0; k < degree; k++) {
        ans *= val;
    }

    return ans;
}

double get_phi(double s, int n, double kmu)
{
    return get_kw(s, n) + kmu * get_koil(s, n);
}

double get_phi(double s, int n, double kmu, double kw)
{
    return kw + kmu * get_koil(s, n);
}

double get_kw(double s, int n)
{
    return my_pow(s, n);
}

double get_koil(double s, int n)
{
    return my_pow((1.0 - s), n);
}

double get_sigma(double s, int n, double kmu)
{
    return get_phi(s, n, kmu); // k = 1;
}

double get_sigma(double s, int n, double kmu, double kw)
{
    return get_phi(s, n, kmu, kw); // k = 1;
}

double get_fbl(double s, int n, double kmu)
{
    if (s < 0.0)
        return 0.0;
    if (s > 1.0)
        return 1.0;
    double kw = get_kw(s, n);
    double sig = get_sigma(s, n, kmu, kw);

    return kw / sig;
}

double get_dfbl(double s, int n, double kmu)
{
    if ((s > 1) || (s < 0))
        return 0.0;
    double kw = get_kw(s, n);
    double dkw = n * my_pow(s, n - 1), dkoil = -n * my_pow((1.0 - s), n - 1);

    double f = get_sigma(s, n, kmu, kw);
    double f2 = f * f;
    double ff = dkw + kmu * dkoil;

    return (dkw * f - ff * kw) / f2;
}

double get_dfbl_approx(double s, int n, double kmu, bool is_left, double d)
{
    double f1 = get_fbl(s, n, kmu);

    double s0 = is_left
        ? s + d
        : s - d;
    
    double f0 = get_fbl(s0, n, kmu);

    return std::abs(f1 - f0) / d;
}

}

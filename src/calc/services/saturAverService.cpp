#include "saturAverService.hpp"

#include <cmath>

namespace ble::src::calc::services {

double SaturAverService::get_satur_aver_analytic(int n, double fw, double kmu)
{
    if (fw > 0.99)
        return 1.0;
    double a = std::pow((fw * kmu) / (1.0 - fw), 1.0 / n);
    return a / (1.0 + a);
}

double SaturAverService::get_satur_aver_num(const std::shared_ptr<mesh::models::Grid> grd, const std::vector<double>& s)
{
    double result = 0.0;
    for (auto& cl : grd->cells) {
        result += cl->volume * s[cl->ind];
    }

    return result / grd->sum_volume;
}

} // namespace ble::src::calc::services

#include "shockFront.hpp"

#include "common/services/workRp.hpp"
#include "logging/logger.hpp"

namespace ble::src::common::services::shock_front {

double get_shock_front(double rp_n, double kmu)
{
    double eps = 0.1; // 2e-1;
    double n = 2000;
    double ds = (1.0 - eps) / n;

    double minDiff = 1e16;
    double result = -1.;

    auto get_shock_front_rhs = [&](double sc) {
        if (std::abs(sc - 0.) < 1e-6) {
            return 1e18;
        }

        double fsc = rp::get_fbl(sc, rp_n, kmu);
        double sdown = 0.;
        double fsdown = rp::get_fbl(sdown, rp_n, kmu);

        return (fsc - fsdown) / (sc - sdown);
    };

    for (int k = 0; k < n; k++) {
        double sc = eps + k * ds;
        double f1 = rp::get_dfbl(sc, rp_n, kmu);
        double f2 = get_shock_front_rhs(sc);

        double diff = std::abs(f1 - f2);
        if (diff < minDiff) {
            minDiff = diff;
            result = sc;
        }
    }

    if (result == eps) {
        logging::write_log("sc value not defined", logging::kWarning);
    }

    return result;
}

} // namespace ble::src

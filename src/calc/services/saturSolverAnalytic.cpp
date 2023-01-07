#include "saturSolverAnalytic.hpp"

#include <math.h>

#include "common/models/physData.hpp"
#include "common/services/commonVector.hpp"
#include "common/services/dataDistributionService.hpp"
#include "common/services/workRp.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

std::vector<std::tuple<double, double>> get_satur_exact(const double sc, const double u,
    const std::shared_ptr<common::models::SolverData> params)
{
    auto get_xs = [&](const double s) {
        if (s < sc)
            return s;

        double ksi0 = 1.0, poro = 1.0;
        double fu = u / poro * cs::rp::get_dfbl(s, params->rp_n, params->kmu);
        switch (params->mesh_setts->type) {
        case common::models::GridType::kRegular:
            return ksi0 - fu;
        case common::models::GridType::kRadial: {
            double a = ksi0 * ksi0 - 2.0 * fu;
            return a < 0.0
                ? 0.0
                : std::sqrt(a);
        }
        default:
            return 0.0;
        }
    };

    double xsc = get_xs(sc);
    std::vector<std::tuple<double, double>> result;

    // initial satur
    int n = params->mesh_setts->n;
    double ds = (xsc - params->rw) / (n - 1);

    for (int k = 0; k < n; k++) {
        double x = params->rw + ds * k;
        double s = src::common::services::DataDistributionService::get_value(x, params->initial_s, 0.0);
        result.push_back(std::make_tuple(x, s));
    }

    // BL
    double s0 = params->bound_satur;
    if (s0 < sc) {
        result.push_back(std::make_tuple(xsc, s0));
        result.push_back(std::make_tuple(1.0, s0));
    } else {
        std::vector<double> ss = common::services::common_vector::make_vector(sc, s0, 100);

        for (auto& s : ss) {
            double x = get_xs(s);
            result.push_back(std::make_tuple(x, s));
        }
    }

    return result;
}

} // namespace ble::src

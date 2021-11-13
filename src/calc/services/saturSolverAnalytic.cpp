#include "saturSolverAnalytic.hpp"

#include <math.h>

#include "common/models/physData.hpp"
#include "common/services/commonVector.hpp"
#include "common/services/workRp.hpp"

namespace cs = ble::src::common::services;

namespace ble::src::calc::services {

std::vector<std::tuple<double, double>> get_satur_exact(const double sc, const double u,
    const std::shared_ptr<common::models::InputData> data)
{
    auto get_xs = [&](const double s) {
        double ksi0 = data->grd->rc, poro = data->phys->poro;
        double fu = u / poro * cs::rp::get_dfbl(s, data->phys);
        switch (data->grd->type) {
        case common::models::GridType::kRegular:
            return ksi0 - fu;
        case common::models::GridType::kRadial: {
            double a = ksi0 * ksi0 - 2.0 * fu;
            return a < 0.0
                ? 0.0
                : std::sqrt(ksi0 * ksi0 - 2.0 * fu);
        }
        default:
            return 0.0;
        }
    };

    double xsc = get_xs(sc);
    std::vector<std::tuple<double, double>> result;
    result.push_back(std::make_tuple(0.0, 0.0));
    result.push_back(std::make_tuple(xsc, 0.0));

    std::vector<double> ss = common::services::make_vector(sc, 1.0, 100);

    for (auto& s : ss) {
        double x = get_xs(s);
        result.push_back(std::make_tuple(x, s));
    }

    return result;
}

} // namespace ble::src

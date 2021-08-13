#include "saturSolverAnalytic.hpp"

#include "common/models/physData.hpp"
#include "common/services/commonVector.hpp"
#include "common/services/workRp.hpp"

namespace cs = ble_src::common::services;

namespace ble_src::calc::services {

double get_xs(const double s, const double u, const double poro,
    const std::shared_ptr<common::models::PhysData> data)
{
    return u / poro * cs::rp::get_dfbl(s, data);
}

std::vector<std::tuple<double, double>> get_satur_exact(const double sc, const double u,
    const std::shared_ptr<common::models::InputData> data)
{
    double xsc = get_xs(sc, u, data->phys->poro, data->phys);

    std::vector<std::tuple<double, double>> result;

    result.push_back(std::make_tuple(0.0, 0.0));
    result.push_back(std::make_tuple(data->grd->l - xsc, 0.0));

    std::vector<double> ss = common::services::make_vector(sc, 1.0, 100);

    for (auto& s : ss) {
        double x = data->grd->l - get_xs(s, u, data->phys->poro, data->phys);
        result.push_back(std::make_tuple(x, s));
    }

    return result;
}

} // namespace ble_src

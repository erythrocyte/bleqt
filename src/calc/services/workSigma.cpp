#include "workSigma.hpp"

#include "common/services/workRp.hpp"

namespace cs = ble::src::common::services;
namespace mm = ble::src::mesh::models;

namespace ble::src::calc::services {

double get_face_sigma(const std::shared_ptr<mm::Face> fc, const std::vector<double> sats,
    const std::shared_ptr<common::models::SolverData> data, const std::shared_ptr<mm::Grid> grd)
{
    auto get_sigma_d = [&](int cind) {
        return (cind == fc->cl1)
            ? std::abs(grd->cells[fc->cl1]->cntr - fc->cntr)
            : (fc->cl2 == -1)
            ? 0.
            : std::abs(grd->cells[fc->cl2]->cntr - fc->cntr);
    };

    double s1 = sats[fc->cl1];
    double s2 = (fc->cl2 == -1)
        ? fc->bound_satur
        : sats[fc->cl2];
    double sig1 = cs::rp::get_sigma(s1, data->rp_n, data->kmu);
    double sig2 = cs::rp::get_sigma(s2, data->rp_n, data->kmu);

    double d1 = get_sigma_d(fc->cl1);
    double d2 = get_sigma_d(fc->cl2);

    double result = (sig1 * sig2 * (d1 + d2)) / (sig2 * d1 + sig1 * d2);

    return result;
}

} // namespace ble::src

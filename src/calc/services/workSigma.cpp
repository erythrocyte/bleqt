#include "workSigma.hpp"

#include "common/services/workRp.hpp"

namespace cs = ble_src::common::services;
namespace mm = ble_src::mesh::models;

namespace ble_src::calc::services {

double get_face_sigma(const std::shared_ptr<mm::Face> fc, const std::vector<double> sats,
    const std::shared_ptr<common::models::PhysData> data, const std::shared_ptr<mm::Grid> grd)
{
    auto get_sigma_d = [&](int cind) {
        return (cind == fc->cl1)
            ? std::abs(grd->cells[fc->cl1]->cntr - fc->x)
            : (fc->cl2 == -1)
            ? 0.
            : std::abs(grd->cells[fc->cl2]->cntr - fc->x);
    };

    double s1 = sats[fc->cl1];
    double s2 = (fc->cl2 == -1)
        ? fc->bound_satur
        : sats[fc->cl2];
    double sig1 = cs::rp::get_sigma(s1, data);
    double sig2 = cs::rp::get_sigma(s2, data);

    double d1 = get_sigma_d(fc->cl1);
    double d2 = get_sigma_d(fc->cl2);

    double result = (sig1 * sig2 * (d1 + d2)) / (sig2 * d1 + sig1 * d2);

    return result;
}

} // namespace ble_src

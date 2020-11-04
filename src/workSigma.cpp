#include "workSigma.hpp"

#include "workRp.hpp"

namespace ble_src {

double get_sigma_d(const std::shared_ptr<Face> fc, int cind, const std::shared_ptr<Grid> grd)
{
    return (cind == fc->cl1)
        ? std::abs(grd->cells[fc->cl1]->cntr - fc->x)
        : (fc->cl2 == -1)
            ? 0.
            : std::abs(grd->cells[fc->cl2]->cntr - fc->x);
}

double get_face_sigma(const std::shared_ptr<Face> fc, const std::vector<double> sats,
    const std::shared_ptr<PhysData> data, const std::shared_ptr<Grid> grd)
{
    double s1 = sats[fc->cl1];
    double s2 = (fc->cl2 == -1)
        ? fc->bound_satur
        : sats[fc->cl2];
    double sig1 = get_sigma(s1, data);
    double sig2 = get_sigma(s2, data);

    double d1 = get_sigma_d(fc, fc->cl1, grd);
    double d2 = get_sigma_d(fc, fc->cl2, grd);

    double result = (sig1 * sig2 * (d1 + d2)) / (sig2 * d1 + sig1 * d2);

    return result;
}

} // namespace ble_src

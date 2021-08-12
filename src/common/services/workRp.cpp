#include "workRp.hpp"

#include <cmath>

namespace ble_src::common::services::rp {

double get_kw(double s, const std::shared_ptr<common::models::PhysData> data)
{
    return std::pow(s, data->n_wat);
}

double get_koil(double s, const std::shared_ptr<common::models::PhysData> data)
{
    return std::pow((1. - s), data->n_oil);
}

double get_sigma(double s, const std::shared_ptr<common::models::PhysData> data)
{
    return get_kw(s, data) + data->kmu * get_koil(s, data);
}

double get_fbl(double s, const std::shared_ptr<common::models::PhysData> data)
{
    double kw = get_kw(s, data);
    double sig = get_sigma(s, data);

    return kw / sig;
}

double get_dfbl(double s, const std::shared_ptr<common::models::PhysData> data)
{
    double kw = get_kw(s, data);
    double nw = data->n_wat, noil = data->n_oil;
    double dkw = nw * std::pow(s, nw - 1), dkoil = -noil * std::pow((1 - s), noil - 1);

    double f = get_sigma(s, data);
    double f2 = f * f;
    double ff = dkw + data->kmu * dkoil;

    return (dkw * f - ff * kw) / f2;
}

}

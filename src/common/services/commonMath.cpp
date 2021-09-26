#include "commonMath.hpp"

namespace ble::src::common::services {

double get_value_lin_approx(const double x0, const double y0, const double x1,
    const double y1, const double val)
{
    double a = (y1 - y0) / (x1 - x0);
    double b = (y1 * x0 - y0 * x1) / (x1 - x0);

    return a * val + b;
}

double get_value_lin_approx(const std::shared_ptr<models::BoundSourceCond> cond, const double v)
{
    return get_value_lin_approx(cond->x0, cond->v0, cond->x1, cond->v1, v);
}

} // namespace ble::src::common_math

#include "commonMath.hpp"

namespace ble_src::common_math {

double get_value_lin_approx(const double x0, const double y0, const double x1,
    const double y1, const double val)
{
    double a = (y1 - y0) / (x1 - x0);
    double b = (y1 * x0 - y0 * x1) / (x1 - x0);

    return a * val + b;
}

} // namespace ble_src::common_math

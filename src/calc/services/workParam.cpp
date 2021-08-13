#include "workParam.hpp"

namespace ble_src::calc::services {

double getULiqInject(const std::shared_ptr<mesh::models::Grid> grd)
{
    double result = 0.;

    for (auto& fc : grd->faces) {
        if (fc->type == mesh::models::FaceType::kContour) {
            result += fc->u;
        }
    }

    return result;
}

} // namespace ble_src
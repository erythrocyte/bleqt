#include "workParam.hpp"

namespace ble_src
{

    double getULiqInject(const std::shared_ptr<Grid> grd)
    {
        double result = 0.;

        for (auto &fc : grd->faces)
        {
            if (fc->type == FaceType::kContour)
            {
                result += fc->u;
            }
        }

        return result;
    }

} // namespace ble_src
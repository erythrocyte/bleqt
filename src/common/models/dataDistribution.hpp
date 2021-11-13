#ifndef BLE_SRC_COMMON_MODELS_BOUNDSOURCECOND_H_
#define BLE_SRC_COMMON_MODELS_BOUNDSOURCECOND_H_

namespace ble::src::common::models {

class DataDistribution {
public:
    DataDistribution()
    {
        x0 = 0.0;
        x1 = 0.0;
        v0 = 0.0;
        v1 = 0.0;
    }

    double x0;
    double x1;
    double v0;
    double v1;
};

}

#endif
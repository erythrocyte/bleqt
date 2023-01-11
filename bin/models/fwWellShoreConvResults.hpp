#ifndef BLE_BIN_MODELS_FWWELLSHORECONVRESULTS_H_
#define BLE_BIN_MODELS_FWWELLSHORECONVRESULTS_H_

#include <iostream>
#include <memory>
#include <vector>

#include "oneFwWellShoreConvData.hpp"

namespace ble::bin::models {

class FwWellShoreConvResults {
public:
    FwWellShoreConvResults() { }
    ~FwWellShoreConvResults() { }

    double fw_conv_delta;
    std::vector<std::shared_ptr<OneFwWellShoreConvData>> data;
};

}

#endif
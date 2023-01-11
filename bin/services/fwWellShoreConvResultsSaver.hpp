#ifndef BLE_BIN_MODELS_FWWELLSHORECONVRESULTSSAVER_H_
#define BLE_BIN_MODELS_FWWELLSHORECONVRESULTSSAVER_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "models/fwWellShoreConvResults.hpp"

namespace ble::bin::services {

class FwWellShoreConvResultsSaver {
public:
    static void save(const std::string& dir_path, const std::shared_ptr<models::FwWellShoreConvResults>);

private:
    FwWellShoreConvResultsSaver() { }
    ~FwWellShoreConvResultsSaver() { }
};

}

#endif
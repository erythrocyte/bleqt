#ifndef BLE_SRC_CALC_MODELS_BLERESULTDATA_H_
#define BLE_SRC_CALC_MODELS_BLERESULTDATA_H_

#include <iostream>
#include <memory>
#include <vector>

#include "common/models/dynamicData.hpp"
#include "common/models/fwData.hpp"
#include "common/models/tauData.hpp"
#include "common/models/wellWorkParams.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::models {
class BleResultData {
public:
    std::shared_ptr<mesh::models::Grid> grd;
    std::vector<std::shared_ptr<common::models::DynamicData>> fields;
    std::vector<std::shared_ptr<common::models::WellWorkParams>> well_work;
    std::vector<std::shared_ptr<common::models::TauData>> tau_t;
    std::vector<std::shared_ptr<common::models::FwData>> aver;

    void clear();
};
} // namespace ble::src

#endif
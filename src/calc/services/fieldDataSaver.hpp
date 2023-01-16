#ifndef BLE_SRC_CALC_SERVICES_FIELDDATASAVER_H_
#define BLE_SRC_CALC_SERVICES_FIELDDATASAVER_H_

#include <iostream>
#include <memory>
#include <string>

#include "common/models/dynamicData.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::services {

class FieldDataSaver {
public:
    static void save(const std::string& fn,
        const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::DynamicData> field);

private:
    FieldDataSaver() { }
    ~FieldDataSaver() { }
};

}

#endif
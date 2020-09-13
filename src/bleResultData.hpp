#ifndef BLESRC_BLERESULTDATA_H_
#define BLESRC_BLERESULTDATA_H_

#include <iostream>
#include <vector>
#include <memory>

#include "dynamicData.hpp"
#include "grid.hpp"
#include "physData.hpp"

namespace ble_src
{
    class BleResultData
    {
    public:
        std::shared_ptr<ble_src::Grid> grd;
        std::vector<std::shared_ptr<DynamicData>> data;
    };
} // namespace ble_src

#endif
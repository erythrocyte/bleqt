#ifndef BLESRC_BLERESULTDATA_H_
#define BLESRC_BLERESULTDATA_H_

#include <iostream>
#include <vector>
#include <memory>

#include "dynamicData.hpp"

namespace ble_src
{
    class BleResultData
    {
    public:
        double length;
        double sc;
        std::vector<std::shared_ptr<DynamicData>> data;
    };
} // namespace ble_src

#endif
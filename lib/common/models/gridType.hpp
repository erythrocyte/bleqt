#ifndef BLE_SRC_COMMON_MODELS_GRIDTYPE_H_
#define BLE_SRC_COMMON_MODELS_GRIDTYPE_H_

#include <iostream>
#include <map>

#include "common/utils/mapInit.hpp"

namespace ble::src::common::models {

struct GridType {

public:
    enum TypeEnum {
        kRegular,
        kRadial,
        // kSpheric
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        case TypeEnum::kRadial:
            return "Radial";
        case TypeEnum::kRegular:
            return "Regular";
        // case TypeEnum::kSpheric:
        //     return "Spheric";
        default:
            return "Undefined";
        }
    }

    static TypeEnum get_enum(std::string val)
    {
        if (val == "Radial")
            return TypeEnum::kRadial;
        // else if (val == "Spheric")
        //     return TypeEnum::kSpheric;
        else
            return TypeEnum::kRegular;
    }
};

typedef common::utils::Iterator<GridType::TypeEnum, 
GridType::TypeEnum::kRegular, 
GridType::TypeEnum::kRadial> GridTypeEnumIterator;

} // namespace ble::src

#endif

#ifndef BLE_SRC_COMMON_MODELS_TIMESTEPTYPE_H_
#define BLE_SRC_COMMON_MODELS_TIMESTEPTYPE_H_

#include <iostream>
#include <map>

#include "common/utils/mapInit.hpp"

namespace ble::src::common::models {

struct TimeStepType {

public:
    enum TypeEnum {
        kOld,
        kNew,
        // kSpheric
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        case TypeEnum::kOld:
            return "Old";
        case TypeEnum::kNew:
            return "New";
        default:
            return "Undefined";
        }
    }

    static TypeEnum get_enum(std::string val)
    {
        if (val == "Old")
            return TypeEnum::kOld;
        else
            return TypeEnum::kNew;
    }
};

typedef common::utils::Iterator<TimeStepType::TypeEnum,
    TimeStepType::TypeEnum::kOld,
    TimeStepType::TypeEnum::kNew>
    TimeStepTypeEnumIterator;

} // namespace ble::src

#endif

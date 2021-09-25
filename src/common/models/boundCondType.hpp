#ifndef BLE_SRC_COMMON_MODELS_BOUNDCONDTYPE_H_
#define BLE_SRC_COMMON_MODELS_BOUNDCONDTYPE_H_

#include "common/utils/mapInit.hpp"

namespace ble::src::common::models {

struct BoundCondType {
public:
    enum TypeEnum {
        kConst,
        kImpermeable,
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        case TypeEnum::kConst:
            return "Const(p=1)";
        case TypeEnum::kImpermeable:
            return "Impermeable";
        default:
            return "Undefined";
        }
    }

    static TypeEnum get_enum(std::string val)
    {
        if (val == "Impermeable")
            return TypeEnum::kImpermeable;
        else
            return TypeEnum::kConst;
    }
};

typedef common::utils::Iterator<BoundCondType::TypeEnum,
    BoundCondType::TypeEnum::kConst,
    BoundCondType::TypeEnum::kImpermeable>
    BoundCondTypeEnumIterator;

} // namespace ble::src

#endif

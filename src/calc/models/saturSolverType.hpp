#ifndef BLE_SRC_CALC_MODELS_SATURSOLVERTYPE_H_
#define BLE_SRC_CALC_MODELS_SATURSOLVERTYPE_H_

#include "common/utils/mapInit.hpp"

namespace ble::src::calc::models {

struct SaturSolverType {
public:
    enum TypeEnum {
        kExplicit,
        kImplicit
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        case TypeEnum::kExplicit:
            return "Explicit";
        case TypeEnum::kImplicit:
            return "Implicit";
        default:
            return "Undefined";
        }
    }

    TypeEnum get_enum(std::string val)
    {
        if (val == "Implicit")
            return TypeEnum::kImplicit;
        else
            return TypeEnum::kExplicit;
    }
};

typedef common::utils::Iterator<SaturSolverType::TypeEnum,
    SaturSolverType::TypeEnum::kExplicit,
    SaturSolverType::TypeEnum::kImplicit>
    SaturSolverTypeEnumIterator;

} // namespace ble::src

#endif

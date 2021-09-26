#ifndef BLE_SRC_COMMON_MODELS_RHSTYPE_H_
#define BLE_SRC_COMMON_MODELS_RHSTYPE_H_

#include "common/utils/mapInit.hpp"

namespace ble::src::common::models {

struct RHSType {
public:
    enum TypeEnum {
        // kConst,
        kFile,
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        // case TypeEnum::kConst:
        //     return "Const(p=1)";
        case TypeEnum::kFile:
            return "File";
        default:
            return "Undefined";
        }
    }

    TypeEnum get_enum(std::string val)
    {
        return TypeEnum::kFile;
        // if (val == "Const")
        //     return TypeEnum::kImpermeable;
        // else
        //     return TypeEnum::kConst;
    }
};

typedef common::utils::Iterator<RHSType::TypeEnum,
    RHSType::TypeEnum::kFile,
    RHSType::TypeEnum::kFile>
    // RHSType::TypeEnum::kConst>
    RHSTypeEnumIterator;

} // namespace ble::src

#endif

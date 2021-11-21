#ifndef BLE_SRC_COMMON_MODELS_RHSTYPE_H_
#define BLE_SRC_COMMON_MODELS_RHSTYPE_H_

#include "common/utils/mapInit.hpp"

namespace ble::src::common::models {

struct DataDistributionType {
public:
    enum TypeEnum {
        kConst,
        kFile,
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        case TypeEnum::kConst:
            return "Const";
        case TypeEnum::kFile:
            return "File";
        default:
            return "Undefined";
        }
    }

    static TypeEnum get_enum(std::string val)
    {
        if (val == "File")
            return TypeEnum::kFile;
        else
            return TypeEnum::kConst;
    }
};

typedef common::utils::Iterator<DataDistributionType::TypeEnum,
    DataDistributionType::TypeEnum::kConst,
    DataDistributionType::TypeEnum::kFile>
    DataDistributionTypeEnumIterator;

} // namespace ble::src

#endif

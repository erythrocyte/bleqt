#ifndef BLE_SRC_MESH_MODELS_FACETYPE_H_
#define BLE_SRC_MESH_MODELS_FACETYPE_H_

namespace ble::src::mesh::models {

struct FaceType {
public:
    enum TypeEnum {
        kWell,
        kContour,
        kInner,
        kTop,
        kBot,
        kUndefined,    
    };

    static std::string get_description(TypeEnum enumVal)
    {
        switch (enumVal) {
        case TypeEnum::kBot:
            return "Bot";
        case TypeEnum::kContour:
            return "Contour";
        case TypeEnum::kInner:
            return "Inner";
        case TypeEnum::kTop:
            return "Top";
        case TypeEnum::kWell:
            return "Well";
        default:
            return "Undefined";
        }
    }

    static TypeEnum get_enum(std::string val)
    {
        if (val == "Bot")
            return TypeEnum::kBot;
        else if (val == "Contour")
            return TypeEnum::kContour;
        else if (val == "Inner")
            return TypeEnum::kInner;
        else if (val == "Top")
            return TypeEnum::kTop;
        else if (val == "Well")
            return TypeEnum::kWell;

        return TypeEnum::kUndefined;
    }
};

}

#endif

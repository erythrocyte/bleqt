#ifndef BLE_GUI_WIDGETS_MODELS_DIMLESSPARAMSDTO_H_
#define BLE_GUI_WIDGETS_MODELS_DIMLESSPARAMSDTO_H_

#include <iostream>

namespace ble::gui::widgets::models {

class DimlessParamsDto {
public:
    DimlessParamsDto() { }
    ~DimlessParamsDto() { }

    double m;
    double rw;
    double l;
    double poro;
    double r;
    double kmu;
    double eps;
    double rp_n;
};

}

#endif
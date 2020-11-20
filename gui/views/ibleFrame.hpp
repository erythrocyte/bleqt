#ifndef BLE_GUI_VIEWS_IBLEFRAME
#define BLE_GUI_VIEWS_IBLEFRAME

#include "fluidParamsWidget.hpp"
#include <iostream>

namespace ble_gui {
namespace views {
    class IBleFrame {
    public:
        virtual ~IBleFrame() { }
        virtual void run() = 0;
        virtual void set_widgets(std::shared_ptr<widgets::FluidParamsVisualWidget> fluidWidget) = 0;


    };
}
}

#endif
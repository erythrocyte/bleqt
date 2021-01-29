#ifndef BLE_GUI_VIEWS_IBLEFRAME
#define BLE_GUI_VIEWS_IBLEFRAME

#include <iostream>

#include "fluidParamsWidget.hpp"
#include "physData.hpp"

namespace ble_gui::views {
class IBleFrame {
public:
    virtual ~IBleFrame() { }
    virtual void run() = 0;
    virtual void set_widgets(std::shared_ptr<widgets::FluidParamsWidget>
            fluidWidget)
        = 0;
    virtual void update_fluid_view(
        const std::shared_ptr<ble_src::PhysData> physData,
        double sc)
        = 0;
};
}

#endif

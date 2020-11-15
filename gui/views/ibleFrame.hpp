#ifndef BLE_GUI_VIEWS_IBLEFRAME
#define BLE_GUI_VIEWS_IBLEFRAME

#include <iostream>

namespace ble_gui {
namespace views {
    class IBleFrame {
    public:
        virtual ~IBleFrame() { }
        virtual void run() = 0;
    };
}
}

#endif
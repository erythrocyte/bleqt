#ifndef BLE_GUI_BLEAPP_H_
#define BLE_GUI_BLEAPP_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

namespace gui {

class BleApplication {
private:
    std::shared_ptr<Hypodermic::Container> m_container;

public:
    BleApplication();
    ~BleApplication();

    void run();
};

}

#endif
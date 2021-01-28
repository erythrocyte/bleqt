#ifndef BLE_GUI_BLEAPP_H_
#define BLE_GUI_BLEAPP_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

namespace ble {

class BleApplication {
private:
    std::shared_ptr<Hypodermic::Container> m_container;

public:
    BleApplication();
    ~BleApplication();

    void run(int argc, char **argv);
};

}

#endif
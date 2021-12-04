#include <iostream>
#include <memory>

#include "bleapp.hpp"

int main(int argc, char** argv)
{
    std::shared_ptr<ble::gui::BleApplication> app(new ble::gui::BleApplication());
    app->run(argc, argv);

    return 0;
}

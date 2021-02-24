#include <iostream>
#include <memory>

#include "bleapp.hpp"

int main(int argc, char** argv)
{
    std::shared_ptr<ble::BleApplication> app(new ble::BleApplication());
    app->run(argc, argv);

    return 1;
}

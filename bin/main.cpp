#include <iostream>
#include <memory>

#include "logging/logger.hpp"
#include "services/calculator.hpp"

int main(int argc, char** argv)
{
    std::string fn = "a.log";
    ble::src::logging::init_log(fn);

    auto calculator = std::make_shared<ble::bin::services::Calculator>();
    // calculator->run_s_const_loop();
    // calculator->run_linear();
    // calculator->run_pv_m();
    calculator->run_stationary_s();

    return 0;
}

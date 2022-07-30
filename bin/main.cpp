#include <iostream>
#include <memory>

#include "logging/logger.hpp"
#include "voids.hpp"

int main(int argc, char** argv)
{
    std::string fn = "a.log";
    ble::src::logging::init_log(fn);

    auto calculator = std::make_shared<ble::bin::Calculator>();
    // auto params = calculator->get_solver_data();
    // auto grd = calculator->get_grid(params);
    // calculator->solve(params, grd);
    calculator->run_s_const_loop();

    return 0;
}

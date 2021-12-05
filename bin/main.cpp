#include <iostream>
#include <memory>

#include "voids.hpp"

int main(int argc, char** argv)
{
    auto calculator = std::make_shared<ble::bin::Calculator>();
    auto params = calculator->get_solver_data();
    auto grd = calculator->get_grid(params);
    calculator->solve(params, grd);

    return 0;
}

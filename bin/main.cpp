#include <iostream>
#include <memory>

#include "voids.hpp"

int main(int argc, char** argv)
{
    auto params = ble::bin::get_solver_data();
    auto grd = ble::bin::get_grid(params);
    ble::bin::solve(params, grd);

    return 0;
}

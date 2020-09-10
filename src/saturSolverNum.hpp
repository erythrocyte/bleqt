#ifndef BLE_SRC_SATURSOLVERNUM_H_
#define BLE_SRC_SATURSOLVERNUM_H_

#include <iostream>
#include <vector>
#include <memory>

#include "inputData.hpp"
#include "grid.hpp"

namespace ble_src {

std::vector<double> solve_satur(const double tau, const std::vector<double>& init, const std::shared_ptr<InputData> data,
		const std::shared_ptr<Grid> grd);

}

#endif

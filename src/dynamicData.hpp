#ifndef BLE_SRC_DYNAMICDATA_H_
#define BLE_SRC_DYNAMICDATA_H_

#include <iostream>
#include <vector>
#include <tuple>

namespace ble_src
{

	class DynamicData
	{
	public:
		double t;
		std::vector<double> p;
		std::vector<double> s;

		std::vector<std::tuple<double, double>> s_an;
	};

} // namespace ble_src

#endif

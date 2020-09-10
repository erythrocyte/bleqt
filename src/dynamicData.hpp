#ifndef BLE_SRC_DYNAMICDATA_H_
#define BLE_SRC_DYNAMICDATA_H_

#include <iostream>
#include <vector>

namespace ble_src
{

	class DynamicData
	{
	public:
		double t;
		std::vector<double> p;
		std::vector<double> s;
	};

} // namespace ble_src

#endif

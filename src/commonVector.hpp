#ifndef BLE_SRC_COMMONVECTOR_H_
#define BLE_SRC_COMMONVECTOR_H_

#include <iostream>
#include <vector>

namespace ble_src
{
    namespace common_vector 
    {
        std::vector<double> make_vector(double begin, double end, int n);
    }
}

#endif
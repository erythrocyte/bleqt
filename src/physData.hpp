#ifndef BLE_SRC_PHYSDATA_H_
#define BLE_SRC_PHYSDATA_H_

namespace ble_src {

class PhysData {
public:
    double kmu; // = mw / moil;
    double n_oil;
    double n_wat;
    double poro = 1.0;
    double perm = 1.0;
};

}

#endif

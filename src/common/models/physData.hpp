#ifndef BLE_SRC_COMMON_MODELS_PHYSDATA_H_
#define BLE_SRC_COMMON_MODELS_PHYSDATA_H_

namespace ble::src::common::models {

class PhysData {
public:
    PhysData(int noil, int nwat, double muw, double muo)
    {
        mu_wat = muw;
        mu_oil = muo;
        k_mu = mu_oil / mu_wat;
        n_oil = noil;
        n_wat = nwat;
    }
    
    double mu_wat;
    double mu_oil;
    int n_oil;
    int n_wat;
    double k_mu;
};

}

#endif

#ifndef BLE_SRC_WORKRP_H_
#define BLE_SRC_WORKRP_H_

namespace ble::src::common::services::rp {

double get_kw(double s, int n);
double get_koil(double s, int n);
double get_fbl(double s, int n, double kmu);
double get_sigma(double s, int n, double kmu);
double get_dfbl(double s, int n, double kmu);
double get_sigma(double s, int n, double kmu, double kw);

} // namespace ble::src

#endif

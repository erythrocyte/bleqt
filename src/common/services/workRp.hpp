#ifndef BLE_SRC_WORKRP_H_
#define BLE_SRC_WORKRP_H_

namespace ble::src::common::services::rp {

double get_kw(double s, double n);
double get_koil(double s, double n);
double get_fbl(double s, double n, double kmu);
double get_sigma(double s, double n, double kmu);
double get_dfbl(double s, double n, double kmu);
double get_sigma(double s, double n, double kmu, double kw);

} // namespace ble::src

#endif

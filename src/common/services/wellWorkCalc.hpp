#ifndef BLE_SRC_COMMON_SERVICES_WELLWORKCALC_H_
#define BLE_SRC_COMMON_SERVICES_WELLWORKCALC_H_

namespace ble::src::common::services::wellworkcalc {
double calc_fw(double ql, double qw);
double calc_qw(double ql, double fw);
double calc_qo(double ql, double fw);

}

#endif
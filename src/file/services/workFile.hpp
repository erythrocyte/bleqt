#ifndef BLE_SRC_FILE_SERVICES_WORKFILE_H_
#define BLE_SRC_FILE_SERVICES_WORKFILE_H_

#include <iostream>
#include <string>

namespace ble_src::file::services{

std::string get_last_line(const std::string fn);

}

#endif
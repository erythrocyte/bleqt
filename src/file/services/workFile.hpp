#ifndef BLE_SRC_FILE_SERVICES_WORKFILE_H_
#define BLE_SRC_FILE_SERVICES_WORKFILE_H_

#include <iostream>
#include <string>
#include <vector>

namespace ble::src::file::services {

std::string get_last_line(const std::string fn);
std::vector<std::string> read_file_from_line(int start_line, const std::string fn);

}

#endif
#ifndef BLE_SRC_COMMON_SERVICES_WORKDIR_H_
#define BLE_SRC_COMMON_SERVICES_WORKDIR_H_

#include <iostream>
#include <string>

namespace ble::src::common::services::work_dir {

void make_dir_my(const std::string& full_path);
std::string combine_dir_my(const std::string& dir1, const std::string& val);
void remove_dir_my(const std::string& full_path);
std::string get_file_dir(const std::string& file_full_path);

}

#endif
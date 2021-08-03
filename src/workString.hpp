#ifndef BLE_SRC_WORKSTRING_H_
#define BLE_SRC_WORKSTRING_H_

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace ble_src {

std::string ltrim(const std::string s);
std::string rtrim(const std::string s);
std::string trim(const std::string s);
std::string trim_erase_end(std::string& ss);
std::vector<std::string> split(const std::string value, const std::string delim);
int to_int(const std::string ss);
double to_dbl(const std::string ss);
std::string replace_symbol(const std::string ss, const std::string searchable,
    const std::string replacable);
bool str_starts_with(std::string const ss, std::string const sub_str);
template <typename... Args>
std::string string_format(const std::string& format, Args... args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
    if (size <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

}

#endif

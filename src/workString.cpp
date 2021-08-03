#include "workString.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace ble_src {

//trim from start
std::string ltrim(const std::string s)
{
    auto result = s;
    result.erase(
        s.begin(),
        std::find_if(
            s.begin(),
            s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return result;
};

// trim from end
std::string rtrim(const std::string s)
{
    auto result = s;
    result.erase(
        std::find_if(
            result.rbegin(),
            result.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace)))
            .base(),
        result.end());
    return result;
};

// trim from both ends
std::string trim(const std::string s)
{
    return ltrim(rtrim(s));
};

std::string trim_erase_end(std::string& ss)
{
    std::string s;
    s = ss;
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    trim(s);
    return s;
};

std::vector<std::string> split(const std::string value, const std::string delim)
{
    std::vector<std::string> result;
    size_t pos = 0;
    std::string token, value2;
    value2 = value;
    value2 = trim_erase_end(value2);
    while ((pos = value2.find(delim)) != std::string::npos) {
        token = value2.substr(0, pos);
        if (token.size() != 0)
            result.push_back(token);
        value2.erase(0, pos + delim.length());
    }
    result.push_back(value2);

    return result;
};

int to_int(const std::string ss)
{
    std::istringstream iss(ss);
    int result;
    iss >> result;
    return result;
};

double to_dbl(const std::string ss)
{
    std::istringstream iss(ss);
    double result;
    iss >> result;
    return result;
};

std::string replace_symbol(const std::string ss, const std::string searchable,
    const std::string replacable)
{
    const size_t mm1 = std::string::npos;
    size_t m = -1;
    std::string result = ss;
    while (true) {
        m = result.find(searchable);
        if (m == mm1)
            break;

        result = result.replace(m, 1, replacable);
    }

    return result;
};

bool str_starts_with(std::string const& ss, std::string const& sub_str)
{
    if (ss.rfind(sub_str, 0) == 0)
        return true;
    else
        return false;
}

}

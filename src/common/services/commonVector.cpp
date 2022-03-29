#include "commonVector.hpp"

#include <fstream>

namespace ble::src::common::services::common_vector {

std::vector<double> make_vector(double begin, double end, int n)
{
    std::vector<double> vec;
    double step = (end - begin) / n;

    vec.reserve(n);
    while (begin <= end) {
        vec.push_back(begin);
        begin += step;
    }

    return vec;
}

std::vector<double> subtract(const std::vector<double>& v1, const std::vector<double>& v2)
{
    std::vector<double> result(v1.size(), 0.0);

    for (size_t i = 0; i < v1.size(); i++) {
        result[i] = v1[i] - v2[i];
    }

    return result;
}

std::vector<double> add(const std::vector<double>& v1, const std::vector<double>& v2)
{
    std::vector<double> result(v1.size(), 0.0);

    for (size_t i = 0; i < v1.size(); i++) {
        result[i] = v1[i] + v2[i];
    }

    return result;
}

void mult_scal(std::vector<double>& v, double s)
{
    for (size_t i = 0; i < v.size(); i++) {
        v[i] *= s;
    }
}

double max_abs(const std::vector<double>& v)
{
    double result = -1.0;
    for (size_t i = 0; i < v.size(); i++) {
        double av = std::abs(v[i]);
        if (av > result)
            result = av;
    }

    return result;
}

void save_vector(const std::string& fn, const std::vector<double>& v)
{
    std::ofstream ofs(fn);
    int iter = 0;
    for (auto& vi : v) {
        ofs << iter << "\t" << vi << std::endl;
        iter++;
    }
    ofs.close();
}

} // namespace common_vector
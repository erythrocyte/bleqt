#include "commonVector.hpp"

namespace ble_src
{
    namespace common_vector
    {
        std::vector<double> make_vector(double begin, double end, int n)
        {
            std::vector<double> vec;
            double step = (end - begin) / n;

            vec.reserve(n);
            while (begin <= end)
            {
                vec.push_back(begin);
                begin += step;
            }

            return vec;
        }
    } // namespace common_vector
}
#include "grid.hpp"

namespace ble::src::mesh::models {

std::tuple<double, double> Grid::get_min_max()
{
    double minx = 1e20;
    double maxx = -1e20;

    for (auto& fc : faces) {
        if (fc->cntr < minx)
            minx = fc->cntr;
        if (fc->cntr > maxx)
            maxx = fc->cntr;
    }

    return std::make_tuple(minx, maxx);
}

}

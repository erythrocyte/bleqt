#include "grid.hpp"

namespace ble::src::mesh::models {

std::tuple<double, double> Grid::get_min_max()
{
    double minx = 1e20;
    double maxx = -1e20;

    for (auto& fc : faces) {
        if (fc->x < minx)
            minx = fc->x;
        if (fc->x > maxx)
            maxx = fc->x;
    }

    return std::make_tuple(minx, maxx);
}

}

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

std::vector<double> Grid::get_cells_centers()
{
    std::vector<double> res;

    for (auto const& cl : cells) {
        res.push_back(cl->cntr);
    }

    return res;
}

}

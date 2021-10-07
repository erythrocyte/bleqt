/*
 * Filename: boundCondData.cpp
 * Path: bleqt/src/common/models
 * Created Date: Thursday, October 7th 2021, 3:10:01 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */


#include "boundCondData.hpp"

#include "common/services/commonMath.hpp"

namespace ble::src::common::models {

double BoundCondData::get_value(double x, double def_val)
{
    for (auto& d : bound_sources) {
        if ((d->x0 <= x) && (x <= d->x1)) {
            return src::common::services::get_value_lin_approx(d, x);
        }
    }

    return def_val;
}


std::tuple<double, double> BoundCondData::get_range(double minx_grd, double maxx_grd)
{
    double result_min = 1e20, result_max = -1e20;
    for (auto& d : bound_sources) {
        if (!(maxx_grd >= d->x0 && minx_grd <= d->x1))
            continue;
        if (d->v0 < result_min)
            result_min = d->v0;
        if (d->v1 < result_min)
            result_min = d->v1;

        if (d->v0 > result_max)
            result_max = d->v0;
        if (d->v1 > result_max)
            result_max = d->v1;
    }

    return std::make_tuple(result_min, result_max);
}

}

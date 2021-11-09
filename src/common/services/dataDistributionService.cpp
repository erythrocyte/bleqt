#include "dataDistributionService.hpp"

#include "common/services/workString.hpp"
#include "file/services/workFile.hpp"
#include "logging/logger.hpp"

namespace ble::src::common::services {

std::vector<std::shared_ptr<models::DataDistribution>> DataDistributionService::get_data_from_file(std::string& file_name)
{
    std::vector<std::shared_ptr<models::DataDistribution>> result;
    if (!file::services::file_exists(file_name))
        return result;

    int line_index = 1;
    std::vector<std::string> data = file::services::read_file_to_vector(file_name);
    for (auto& d : data) {
        if (str_starts_with(d, "#"))
            continue;
        std::vector<std::string> dd = split(d, " ");
        if (dd.size() != 4)
            continue;

        auto bsc = std::make_shared<models::DataDistribution>();
        bsc->x0 = to_dbl(dd[0]);
        bsc->x1 = to_dbl(dd[1]);
        bsc->v0 = to_dbl(dd[2]);
        bsc->v1 = to_dbl(dd[3]);

        if (result.size() > 0) {
            double x1 = result[result.size() - 1]->x1;
            if (std::abs(x1 - bsc->x0) > 1e-8) {
                result.clear();
                std::string mess = services::string_format("bad line with rhs: %i", line_index);
                logging::write_log(mess, logging::kWarning);
                break;
            }
        }

        line_index++;

        result.push_back(bsc);
    }

    return result;
}

std::vector<std::shared_ptr<models::DataDistribution>> DataDistributionService::get_data_from_const(
    double const_val, int len_right_prec, double x0, double x1)
{
    std::vector<std::shared_ptr<models::DataDistribution>> result;
    double len = x1 - x0;

    auto bsc = std::make_shared<models::DataDistribution>();
    bsc->x1 = x1;
    bsc->x0 = len * (1.0 - (double)len_right_prec / 100.0);
    bsc->v0 = const_val;
    bsc->v1 = const_val;
    result.push_back(bsc);

    if (len_right_prec < 100) {
        bsc = std::make_shared<models::DataDistribution>();
        bsc->x1 = len * (1.0 - (double)len_right_prec / 100.0);
        bsc->x0 = x0;
        bsc->v0 = 0.0;
        bsc->v1 = 0.0;
        result.push_back(bsc);
    }

    return result;
}

}
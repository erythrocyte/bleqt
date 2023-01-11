#include "fwWellShoreConvResultsSaver.hpp"

#include <fstream>

#include "common/services/workDir.hpp"
#include "common/services/workString.hpp"

namespace cs = ble::src::common::services;

namespace ble::bin::services {

void FwWellShoreConvResultsSaver::save(const std::string& dir_path,
    const std::shared_ptr<models::FwWellShoreConvResults> results)
{
    std::string file_name = cs::string_format("fw_delta_%.5f.dat", results->fw_conv_delta);
    std::string file_path = cs::work_dir::combine_dir_my(dir_path, file_name);

    std::ofstream file;
    file.open(file_path);
    file << "M\tPV\n";

    for (auto const& d : results->data) {
        file << d->m << "\t" << d->pv << "\n";
    }

    file.close();
}

}
#include "fieldDataSaver.hpp"

#include <fstream>

namespace ble::src::calc::services {

void FieldDataSaver::save(const std::string& fn,
    const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::DynamicData> field)
{
    std::ofstream file;
    file.open(fn);
    file << "x\tp\ts\n";

    for (auto const& cl : grd->cells) {
        file << cl->cntr << "\t" << field->p[cl->ind] << "\t" << field->s[cl->ind] << "\n";
    }

    file.close();
}

}

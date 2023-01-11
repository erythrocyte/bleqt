#include "bleResultData.hpp"

namespace ble::src::calc::models {

void BleResultData::clear()
{
    this->aver.clear();
    this->fields.clear();
    this->tau_t.clear();
    this->well_work.clear();
}

} // namespace ble::src

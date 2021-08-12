#ifndef BLESRC_CALC_MODELS_BLECALC_H_
#define BLESRC_CALC_MODELS_BLECALC_H_

#include <functional>
#include <iostream>
#include <memory>

#include "bleResultData.hpp"
#include "common/models/inputData.hpp"
#include "mesh/models/grid.hpp"

namespace ble_src::calc::models {
class BleCalc {
private:
    std::shared_ptr<BleResultData> _results;
    void set_initial_cond(size_t n);
    void save_press(int index, const std::shared_ptr<mesh::models::Grid> grd,
        const std::vector<double> p);

public:
    BleCalc();
    ~BleCalc();
    void calc(const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::InputData> data,
        std::function<void(double)> set_progress);

    size_t get_data_len() { return _results->data.size(); }

    std::shared_ptr<common::models::DynamicData> get_data(int index) const { return _results->data[index]; }

    std::shared_ptr<BleResultData> get_result() { return _results; }
};
} // namespace ble_src

#endif
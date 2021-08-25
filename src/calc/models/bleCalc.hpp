#ifndef BLESRC_CALC_MODELS_BLECALC_H_
#define BLESRC_CALC_MODELS_BLECALC_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "bleResultData.hpp"
#include "common/models/inputData.hpp"
#include "common/models/wellWorkParams.hpp"
#include "mesh/models/grid.hpp"

namespace ble_src::calc::models {
class BleCalc {
public:
    BleCalc();
    ~BleCalc();
    void calc(const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::InputData> data,
        std::function<void(double)> set_progress);

    size_t get_data_len() { return _results->data.size(); }
    std::shared_ptr<common::models::DynamicData> get_data(int index) const { return _results->data[index]; }
    std::shared_ptr<BleResultData> get_result() { return _results; }
    std::vector<std::shared_ptr<common::models::WellWorkParams>> get_well_work_params() { return _wellWorkParams; }

private:
    std::shared_ptr<BleResultData> _results;
    std::vector<std::shared_ptr<common::models::WellWorkParams>> _wellWorkParams;

    void set_initial_cond(size_t n);
    void save_press(int index, const std::shared_ptr<mesh::models::Grid> grd,
        const std::vector<double> p);
};
} // namespace ble_src

#endif
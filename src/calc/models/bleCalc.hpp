#ifndef BLE_SRC_CALC_MODELS_BLECALC_H_
#define BLE_SRC_CALC_MODELS_BLECALC_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "bleResultData.hpp"
#include "common/models/inputData.hpp"
#include "common/models/wellWorkParams.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::models {
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

    void set_initial_cond(const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::InputData> data);
    void save_vals(double t, const std::shared_ptr<mesh::models::Grid> grd,
        const std::vector<std::string>&caps, const std::vector<std::vector<double>>& vals);
    void save_any_vector(const std::vector<std::tuple<double, double>>& v, const std::string& fn);
    void save_faces_val(const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::InputData> data);
};
} // namespace ble::src

#endif
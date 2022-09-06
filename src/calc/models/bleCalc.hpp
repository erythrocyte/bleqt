#ifndef BLE_SRC_CALC_MODELS_BLECALC_H_
#define BLE_SRC_CALC_MODELS_BLECALC_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "bleResultData.hpp"
#include "calc/models/averFwSaveData.hpp"
#include "common/models/fwData.hpp"
#include "common/models/solverData.hpp"
#include "common/models/tauData.hpp"
#include "common/models/wellWorkParams.hpp"
#include "mesh/models/grid.hpp"

namespace ble::src::calc::models {
class BleCalc {
public:
    BleCalc();
    ~BleCalc();
    void calc(const std::shared_ptr<mesh::models::Grid> grd,
        const std::shared_ptr<common::models::SolverData> data,
        std::function<void(double)> set_progress,
        bool clear_aver);

    size_t get_data_len() { return _results->data.size(); }
    std::shared_ptr<common::models::DynamicData> get_data(int index) const { return _results->data[index]; }
    std::shared_ptr<BleResultData> get_result() { return _results; }
    std::vector<std::shared_ptr<common::models::WellWorkParams>> get_well_work_params() { return _wellWorkParams; }
    std::vector<std::shared_ptr<common::models::TauData>> get_tau_data() { return m_tau_data; }
    std::vector<std::shared_ptr<common::models::FwData>> get_aver_fw_data() { return m_fw_data; }
    double get_period();

private:
    std::shared_ptr<BleResultData> _results;
    std::vector<std::shared_ptr<common::models::WellWorkParams>> _wellWorkParams;
    std::vector<std::shared_ptr<common::models::TauData>> m_tau_data;
    std::vector<std::shared_ptr<common::models::FwData>> m_fw_data;
    double m_sum_t;
    std::shared_ptr<mesh::models::Grid> m_grd;
    std::shared_ptr<common::models::SolverData> m_data;

    void set_initial_cond();
    void save_press(int index, const std::vector<double> p);
    void save_any_vector(const std::vector<std::tuple<double, double>>& v, const std::string& fn);
    void save_faces_val();
    void add_aver_fw(double pv, double fw, double fw_shore, const std::vector<double> s);
    void check_conservative();
    void save_aver_fw(const char* fn, const std::shared_ptr<AverFwSaveData> data);

    void save_pvi_s(double pvi, double pvi_fake, std::vector<double> s, double m);
};
} // namespace ble::src

#endif
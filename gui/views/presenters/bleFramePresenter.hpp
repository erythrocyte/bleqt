#ifndef BLE_GUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_
#define BLE_GUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_

#include <iostream>
#include <memory>
#include <tuple>

#include "Hypodermic/Hypodermic.h"

#include "bleFrame.hpp"
#include "blePresenter.hpp"
#include "boundVisualWidgetPresenter.hpp"
#include "common/models/inputData.hpp"
#include "conditionsWidgetPresenter.hpp"
#include "dataWidgetPresenter.hpp"
#include "dimlesParamsWidgetPresenter.hpp"
#include "fluidParamGraphWidgetPresenter.hpp"
#include "fwVisualWidgetPresenter.hpp"
#include "gridSettsWidgetPresenter.hpp"
#include "logging/logger.hpp"
#include "resultDataWidgetPresenter.hpp"
#include "satSolverSettsWidgetPresenter.hpp"
#include "shockFrontSettsWidgetPresenter.hpp"
#include "tauVisualWidgetPresenter.hpp"
#include "wellWorkDataWidgetPresenter.hpp"

namespace bwp = ble::gui::widgets::presenters;

namespace ble::gui::views::presenters {

class BleFramePresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BleFrame> view);
    ~BleFramePresenter() { }
    void run();
    std::shared_ptr<BleFrame> get_view();

private:
    int m_log_line_start_index;

    std::shared_ptr<bwp::DataWidgetPresenter> m_dataWidgetPresenter;
    std::shared_ptr<bwp::ConditionsWidgetPresenter> m_conditionsWidgetPresenter;
    std::shared_ptr<bwp::SatSolverSettsWidgetPresenter> m_satsolver_presenter;
    std::shared_ptr<bwp::GridSettsWidgetPresenter> m_gridsetts_presenter;
    std::shared_ptr<bwp::ShockFrontSettsWidgetPresenter> m_shockfront_presenter;

    std::shared_ptr<bwp::FluidParamGraphWidgetPresenter> m_fluidWidgetPresenter;
    std::shared_ptr<bwp::ResultDataWidgetPresenter> m_resultDataWidgetPresenter;
    std::shared_ptr<bwp::WellWorkDataWidgetPresenter> m_wellWorkDataWidgetPresenter;
    std::shared_ptr<bwp::BoundVisualWidgetPresenter> m_boundVisualPresenter;
    std::shared_ptr<bwp::TauVisualWidgetPresenter> m_tauVisualPresenter;
    std::shared_ptr<bwp::FwVisualWidgetPresenter> m_fwVisualPresenter;
    std::shared_ptr<bwp::DimlesParamsWidgetPresenter> m_dimlesParamsPresenter;

    void set_signals();
    double get_sc();
    void update_progress(double perc) { get_view()->update_progress(perc); }
    void set_status(const QString& str) { get_view()->set_status(str); }
    void init_log();
    std::tuple<std::string, ble::src::logging::SeverityLevelEnum> parse_log_mess(std::string mess);
    std::shared_ptr<ble::src::common::models::InputData> get_data();
    void update_dimless_params();

private slots:
    void onShowShockFrontCurve(bool status);
    void onRpValuesUpdated();
    void on_run_calc();
    void handleFileChanged(QString str);
    void on_update_rhs_tab();
    void on_dimless_params_changed();
};
}

#endif

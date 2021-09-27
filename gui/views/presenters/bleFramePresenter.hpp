#ifndef BLE_GUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_
#define BLE_GUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_

#include <iostream>
#include <memory>
#include <tuple>

#include "Hypodermic/Hypodermic.h"

#include "bleFrame.hpp"
#include "blePresenter.hpp"
#include "dataWidgetPresenter.hpp"
#include "fluidParamGraphWidgetPresenter.hpp"
#include "logging/logger.hpp"
#include "resultDataWidgetPresenter.hpp"
#include "wellWorkDataWidgetPresenter.hpp"
#include "boundaryCondResultWidgetPresenter.hpp"

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
    std::shared_ptr<bwp::FluidParamGraphWidgetPresenter> m_fluidWidgetPresenter;
    std::shared_ptr<bwp::DataWidgetPresenter> m_dataWidgetPresenter;
    std::shared_ptr<bwp::ResultDataWidgetPresenter> m_resultDataWidgetPresenter;
    std::shared_ptr<bwp::WellWorkDataWidgetPresenter> m_wellWorkDataWidgetPresenter;
    std::shared_ptr<bwp::BoundaryCondResultWidgetPresenter> m_boundCondResultPresenter;

    void set_signals();
    double get_sc();
    void update_progress(double perc) { get_view()->update_progress(perc); }
    void set_status(const QString& str) { get_view()->set_status(str); }
    void init_log();    
    std::tuple<std::string, ble::src::logging::SeverityLevelEnum> parse_log_mess(std::string mess);

private slots:
    void onShowShockFrontCurve(bool status);
    void onRpValuesUpdated();
    void on_run_calc();
    void handleFileChanged(QString str);
    void on_update_rhs_tab();
};
}

#endif

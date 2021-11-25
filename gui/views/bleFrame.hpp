#ifndef BLE_GUI_BLEFRAME_H_
#define BLE_GUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "boundVisualWidget.hpp"
#include "conditionsWidget.hpp"
#include "dataWidget.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "gridSettsWidget.hpp"
#include "logging/logger.hpp"
#include "resultDataWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"
#include "tauVisualWidget.hpp"
#include "ui_bleFrame.hpp"
#include "wellWorkDataWidget.hpp"

#include <QMainWindow>

namespace ble::gui::views {

class BleFrame : public QMainWindow, private UI::UI_BleFrame {
    Q_OBJECT
public:
    explicit BleFrame(QWidget* parent = nullptr);

    ~BleFrame() { delete ui; }

    void run() { show(); }

    void set_widgets(
        std::shared_ptr<widgets::DataWidget> dataWidget,
        std::shared_ptr<widgets::ConditionsWidget> conditionsWidget,
        std::shared_ptr<widgets::SatSolverSettsWidget> satsolver_widget,
        std::shared_ptr<widgets::GridSettsWidget> gridsetts_widget,
        std::shared_ptr<widgets::ShockFrontSettsWidget> shockfront_widget,

        std::shared_ptr<widgets::FluidParamsGraphWidget> fluidParamsWidget,
        std::shared_ptr<widgets::ResultDataWidget> resultDataWidget,
        std::shared_ptr<widgets::WellWorkDataWidget> wellWorkDataWidget,
        std::shared_ptr<widgets::BoundVisualWidget> condWidget,
        std::shared_ptr<widgets::TauVisualWidget> tauWidget);
    void update_progress(double perc) { ui->statusProgressBar->setValue(perc); }
    void set_status(QString str) { ui->statusLabel->setText(str); }
    void add_log_message(std::string str, ble::src::logging::SeverityLevelEnum level);

signals:
    void sgn_run_calc();

private:
    UI::UI_BleFrame* ui;
    void set_settings_widget(std::shared_ptr<widgets::DataWidget> dataWidget,
        std::shared_ptr<widgets::ConditionsWidget> conditionsWidget,
        std::shared_ptr<widgets::SatSolverSettsWidget> satsolver_widget,
        std::shared_ptr<widgets::GridSettsWidget> gridsetts_widget,
        std::shared_ptr<widgets::ShockFrontSettsWidget> shockfront_widget);

private slots:
    void handleRunButton() { emit sgn_run_calc(); }
};

} // namespace ble_gui::views

#endif

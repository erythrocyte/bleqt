#ifndef BLEGUI_BLEFRAME_H_
#define BLEGUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "dataWidget.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "resultDataWidget.hpp"
#include "ui_bleFrame.hpp"
#include "logging/logger.hpp"

#include <QMainWindow>

namespace ble_gui::views {

class BleFrame : public QMainWindow, private UI::UI_BleFrame { //, public IBleFrame {
    Q_OBJECT
public:
    explicit BleFrame(QWidget* parent = nullptr);

    ~BleFrame() { delete ui; }

    void run() { show(); }

    void set_widgets(std::shared_ptr<widgets::FluidParamsGraphWidget> fluidParamsWidget,
        std::shared_ptr<widgets::ResultDataWidget> resultDataWidget,
        std::shared_ptr<widgets::DataWidget> dataWidget);
    void update_progress(double perc) { ui->statusProgressBar->setValue(perc); }
    void set_status(QString str) { ui->statusLabel->setText(str); }
    void add_log_message(std::string str, ble_src::logging::SeverityLevelEnum level);

signals:
    void sgn_run_calc();

private:
    UI::UI_BleFrame* ui;
    void set_settings_widget(std::shared_ptr<widgets::DataWidget> dataWidget);

private slots:
    void handleRunButton() { emit sgn_run_calc(); }
};

} // namespace ble_gui::views

#endif

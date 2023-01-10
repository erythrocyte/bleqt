#ifndef BLE_GUI_BLEFRAME_H_
#define BLE_GUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "logging/logger.hpp"
#include "models/settingsWidgetsDto.hpp"
#include "models/viewWidgetsDto.hpp"
#include "ui_bleFrame.hpp"

#include <QMainWindow>

namespace ble::gui::views {

class BleFrame : public QMainWindow, private UI::UI_BleFrame {
    Q_OBJECT
public:
    explicit BleFrame(QWidget* parent = nullptr);

    ~BleFrame() { delete ui; }

    void run() { show(); }

    void set_widgets(const std::shared_ptr<models::ViewWidgetsDto> widgets);
    void update_progress(double perc) { ui->statusProgressBar->setValue(perc); }
    void set_status(QString str) { ui->statusLabel->setText(str); }
    void add_log_message(std::string str, ble::src::logging::SeverityLevelEnum level);

signals:
    void sgn_run_calc();

private:
    UI::UI_BleFrame* ui;
    void set_settings_widget(const std::shared_ptr<models::SettingsWidgetsDto> widgets);

private slots:
    void handleRunButton() { emit sgn_run_calc(); }
};

} // namespace ble_gui::views

#endif

#ifndef BLE_GUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_

#include <iostream>
#include <memory>
#include <string>

#include "common/models/shockFrontSettings.hpp"
#include "uis/ui_shockFrontSettsWidget.hpp"

namespace ble::gui::widgets {

class ShockFrontSettsWidget : public QWidget, private UI::ShockFrontSetts {
    Q_OBJECT
public:
    ShockFrontSettsWidget(QWidget* parent = nullptr);
    ~ShockFrontSettsWidget() { delete ui; }

    void SetShockFrontValue(double value);
    void set_show_shockfront_status(bool status);
    void set_block(bool status);
    std::shared_ptr<src::common::models::ShockFrontSettings> get_data();

signals:
    void showShockFrontCurve(bool status);

private:
    UI::ShockFrontSetts* ui;

private slots:
    void changeCheckStatus() { emit showShockFrontCurve(ui->showCurve->isChecked()); }
};

} // namespace ble_gui::widgets

#endif

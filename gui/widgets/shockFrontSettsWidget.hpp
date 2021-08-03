#ifndef BLEGUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_
#define BLEGUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_

#include <iostream>
#include <memory>
#include <string>

#include "uis/ui_shockFrontSettsWidget.hpp"

namespace ble_gui ::widgets {

class ShockFrontSettsWidget : public QWidget, private UI::ShockFrontSetts {
    Q_OBJECT
public:
    ShockFrontSettsWidget(QWidget* parent = nullptr);
    ~ShockFrontSettsWidget() { delete ui; }

    void SetShockFrontValue(double value);
    void set_show_shockfront_status(bool status);

signals:
    void showShockFrontCurve(bool status);

private:
    UI::ShockFrontSetts* ui;

private slots:
    void changeCheckStatus() { emit showShockFrontCurve(ui->showCurve->isChecked()); }
};

} // namespace ble_gui::widgets

#endif

#ifndef BLEGUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_
#define BLEGUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_

#include <iostream>
#include <memory>
#include <string>

#include "uis/ui_shockFrontSettsWidget.hpp"

namespace ble_gui {
namespace widgets {
    class ShockFrontSettsWidget : public QWidget, private UI::ShockFrontSetts {
        Q_OBJECT
    public:
        ShockFrontSettsWidget(QWidget* parent = nullptr);
        ~ShockFrontSettsWidget() { delete ui; }

        void SetShockFrontValue(std::string value);

    signals:
        void checkBoxStatusChanged(bool status);

    private:
        UI::ShockFrontSetts* ui;

    private slots:
        void changeCheckStatus() { emit checkBoxStatusChanged(ui->showCurve->isChecked()); }
    };
} // namespace widgets
} // namespace ble_gui

#endif
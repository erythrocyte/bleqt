#ifndef BLE_GUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_SHOCKFRONTSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QCheckBox>
#include <QLabel>

namespace ble_gui
{
    namespace widgets
    {
        class ShockFrontSettsWidget : public QWidget
        {
            Q_OBJECT
        public:
            ShockFrontSettsWidget(QWidget *parent = nullptr);
            ~ShockFrontSettsWidget() {}

            QLabel *shockFrontValue;
            QCheckBox *showCurve;
        };
    } // namespace widgets

} // namespace ble_gui

#endif
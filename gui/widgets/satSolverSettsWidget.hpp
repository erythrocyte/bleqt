#ifndef BLEGUI_WIDGETS_SATSOLVERSETTSWIDGET_H_
#define BLEGUI_WIDGETS_SATSOLVERSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_satSolverSettsWidget.hpp"

namespace ble_gui::widgets {

class SatSolverSettsWidget : public QWidget, private UI::SaturSolverSetts {
    Q_OBJECT
public:
    SatSolverSettsWidget(QWidget* parent = nullptr);
    ~SatSolverSettsWidget() { delete ui; }

    double getCurantVal() const { return ui->Curant->value(); }
    int getPressRecalcN() const { return ui->RecalcPressN->value(); }

private:
    UI::SaturSolverSetts* ui;
};

} // namespace ble_gui::widgets

#endif
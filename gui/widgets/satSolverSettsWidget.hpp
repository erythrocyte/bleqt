#ifndef BLE_GUI_WIDGETS_SATSOLVERSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_SATSOLVERSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_satSolverSettsWidget.hpp"

namespace ble::gui::widgets {

class SatSolverSettsWidget : public QWidget, private UI::SatSolverSetts {
    Q_OBJECT
public:
    SatSolverSettsWidget(QWidget* parent = nullptr);
    ~SatSolverSettsWidget() { delete ui; }

    double getCurantVal() const { return ui->Curant->value(); }
    int getPressRecalcN() const { return ui->RecalcPressN->value(); }
    bool need_satur_solver() const { return ui->NeedSaturSolve->isChecked(); }

private:
    UI::SatSolverSetts* ui;
};

} // namespace ble_gui::widgets

#endif
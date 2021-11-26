#ifndef BLE_GUI_WIDGETS_SATSOLVERSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_SATSOLVERSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include "calc/models/saturSolverType.hpp"
#include "uis/ui_satSolverSettsWidget.hpp"

namespace ble::gui::widgets {

class SatSolverSettsWidget : public QWidget, private UI::SatSolverSetts {
    Q_OBJECT
public:
    SatSolverSettsWidget(QWidget* parent = nullptr);
    ~SatSolverSettsWidget() { delete ui; }

    double getCurantVal() const { return ui->Curant->value(); }
    int getPressRecalcN() const { return ui->RecalcPressN->value(); }
    bool need_satur_solve() const { return ui->NeedSaturSolve->isChecked(); }
    src::calc::models::SaturSolverType::TypeEnum solver_type();

private:
    UI::SatSolverSetts* ui;
};

} // namespace ble_gui::widgets

#endif
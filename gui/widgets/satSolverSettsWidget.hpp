#ifndef BLE_GUI_WIDGETS_SATSOLVERSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_SATSOLVERSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include "calc/models/saturSolverSettings.hpp"
#include "calc/models/saturSolverType.hpp"
#include "uis/ui_satSolverSettsWidget.hpp"

namespace ble::gui::widgets {

class SatSolverSettsWidget : public QWidget, private UI::SatSolverSetts {
    Q_OBJECT
public:
    SatSolverSettsWidget(QWidget* parent = nullptr);
    ~SatSolverSettsWidget() { delete ui; }

    std::shared_ptr<src::calc::models::SaturSolverSetts> get_data();

private:
    UI::SatSolverSetts* ui;
};

} // namespace ble_gui::widgets

#endif
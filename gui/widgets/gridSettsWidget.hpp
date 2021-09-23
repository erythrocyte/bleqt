#ifndef BLE_GUI_WIDGETS_GRIDSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_GRIDSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QWidget>

#include "uis/ui_gridSettsWidget.hpp"

namespace ble::gui::widgets {

class GridSettsWidget : public QWidget, private UI::GridSetts {
    Q_OBJECT
public:
    GridSettsWidget(QWidget* parent = nullptr);
    ~GridSettsWidget() { delete ui; }

    double getLenght() const { return ui->Length->value(); }
    int getCellCount() const { return ui->CellCount->value(); }

private:
    UI::GridSetts* ui;
};

} // namespace ble_gui::widgets

#endif
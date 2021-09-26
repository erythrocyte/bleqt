#ifndef BLE_GUI_WIDGETS_BOUNDARYCONDITIONSWIDGET_H_
#define BLE_GUI_WIDGETS_BOUNDARYCONDITIONSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "uis/ui_boundaryConditionsWidget.hpp"

namespace ble::gui::widgets {

class BoundaryConditionsWidget : public QWidget, private UI::BoundaryConditions {
    Q_OBJECT
public:
    BoundaryConditionsWidget(QWidget* parent = nullptr);
    ~BoundaryConditionsWidget() { delete ui; }

    // double getLenght() const { return ui->WellRadius->value(); }
    // int getCellCount() const { return ui->CellCount->value(); }

private:
    UI::BoundaryConditions* ui;

    void set_items();
    void subscribe();

private slots:
    void contourTypeChanged(const QString&);
    void rhsTypeChanged(const QString&);
    void fileChooseClicked();
};

} // namespace ble_gui::widgets

#endif
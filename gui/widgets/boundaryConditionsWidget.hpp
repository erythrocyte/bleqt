#ifndef BLE_GUI_WIDGETS_BOUNDARYCONDITIONSWIDGET_H_
#define BLE_GUI_WIDGETS_BOUNDARYCONDITIONSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "common/models/boundCondData.hpp"
#include "uis/ui_boundaryConditionsWidget.hpp"

namespace ble::gui::widgets {

class BoundaryConditionsWidget : public QWidget, private UI::BoundaryConditions {
    Q_OBJECT
public:
    BoundaryConditionsWidget(QWidget* parent = nullptr);
    ~BoundaryConditionsWidget() { delete ui; }

    std::shared_ptr<src::common::models::BoundCondData> get_bound_data(double x0, double x1);

signals:
    void rhs_updated();

private:
    UI::BoundaryConditions* ui;

    void set_items();
    void subscribe();

private slots:
    void contourTypeChanged(const QString&);
    void rhsTypeChanged(const QString&);
    void fileChooseClicked();
    void onRhsConstValueChanged(double);
    void onRhsConstLenghtChanged(int);
};

} // namespace ble_gui::widgets

#endif
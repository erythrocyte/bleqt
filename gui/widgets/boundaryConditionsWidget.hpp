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

signals:
    void get_bound_data(const std::shared_ptr<src::common::models::BoundCondData> bound_data);
    void rhs_updated();

private:
    UI::BoundaryConditions* ui;

    void set_items();
    void subscribe();
    std::shared_ptr<src::common::models::BoundCondData> prepare_data(bool is_file);

private slots:
    void contourTypeChanged(const QString&);
    void rhsTypeChanged(const QString&);
    void fileChooseClicked();
};

} // namespace ble_gui::widgets

#endif
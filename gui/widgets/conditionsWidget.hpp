#ifndef BLE_GUI_WIDGETS_CONDITIONSWIDGET_H_
#define BLE_GUI_WIDGETS_CONDITIONSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "common/models/boundCondData.hpp"
#include "uis/ui_conditionsWidget.hpp"

namespace ble::gui::widgets {

class ConditionsWidget : public QWidget, private UI::Conditions {
    Q_OBJECT
public:
    ConditionsWidget(QWidget* parent = nullptr);
    ~ConditionsWidget() { delete ui; }

    std::shared_ptr<src::common::models::BoundCondData> get_bound_data(double x0, double x1);

signals:
    void rhs_updated();

private:
    UI::Conditions* ui;

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
#ifndef BLE_GUI_WIDGETS_MODELDATAWIDGET_H_
#define BLE_GUI_WIDGETS_MODELDATAWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_modelDataWidget.hpp"

namespace ble::gui::widgets {
class ModelDataWidget : public QWidget, private UI::ModelData {
    Q_OBJECT
public:
    ModelDataWidget(QWidget* parent = nullptr);
    ~ModelDataWidget() { delete ui; }

    double getModelingPeriod() const { return ui->Period->value(); }
    double get_save_fields_step() const { return ui->SaveFieldSteps->value(); }
    double get_bound_satur() const { return ui->BoundSatur->value(); }

private:
    UI::ModelData* ui;

private slots:
    void modeling_period_changed(double value);
};

} // namespace ble_gui::widgets

#endif

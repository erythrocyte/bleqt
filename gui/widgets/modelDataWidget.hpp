#ifndef BLEGUI_WIDGETS_MODELDATAWIDGET_H_
#define BLEGUI_WIDGETS_MODELDATAWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_modelDataWidget.hpp"

namespace ble_gui::widgets {
class ModelDataWidget : public QWidget, private UI::ModelData {
    Q_OBJECT
public:
    ModelDataWidget(QWidget* parent = nullptr);
    ~ModelDataWidget() { delete ui; }

    double getModelingPeriod() const { return ui->Period->value(); }

private:
    UI::ModelData* ui;
};

} // namespace ble_gui::widgets

#endif

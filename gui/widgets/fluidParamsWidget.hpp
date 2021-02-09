#ifndef BLEGUI_WIDGETS_FLUIDPARAMSVISUALWIDGET_H_
#define BLEGUI_WIDGETS_FLUIDPARAMSVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "models/fluidParamsModel.hpp"
#include "physData.hpp"
#include "uis/ui_fluidParamsWidget.hpp"

namespace ble_gui::widgets {

class FluidParamsWidget : public QWidget, private UI::FluidParams {
    Q_OBJECT

public:
    FluidParamsWidget(QWidget* parent = nullptr);
    ~FluidParamsWidget() { delete ui; }

    void update_view(const std::shared_ptr<ble_src::PhysData> physData, double sc);

signals:
    std::shared_ptr<ble_gui::widgets::models::FluidParamsModel> get_data(const std::shared_ptr<ble_src::PhysData> physData, double sc);

private:
    UI::FluidParams* ui;
};

} // namespace ble_gui::widgets

#endif
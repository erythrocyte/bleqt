#ifndef BLEGUI_WIDGETS_FLUIDPARAMSGRAPHWIDGET_H_
#define BLEGUI_WIDGETS_FLUIDPARAMSGRAPHWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "models/fluidParamsModel.hpp"
#include "physData.hpp"
#include "uis/ui_fluidParamsWidget.hpp"

namespace ble_gui::widgets {

class FluidParamsGraphWidget : public QWidget, private UI::FluidParams {
    Q_OBJECT

public:
    FluidParamsGraphWidget(QWidget* parent = nullptr);
    ~FluidParamsGraphWidget() { delete ui; }

    void update_view(const std::shared_ptr<ble_src::PhysData> physData, double sc);

signals:
    std::shared_ptr<ble_gui::widgets::models::FluidParamsModel> get_data(const std::shared_ptr<ble_src::PhysData> physData, double sc);

private:
    UI::FluidParams* ui;
};

} // namespace ble_gui::widgets

#endif
#ifndef BLEGUI_WIDGETS_FLUIDPARAMSGRAPHWIDGET_H_
#define BLEGUI_WIDGETS_FLUIDPARAMSGRAPHWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "common/models/physData.hpp"
#include "models/fluidParamsDto.hpp"
#include "uis/ui_fluidParamsWidget.hpp"

namespace wmf = ble_gui::widgets::models;

namespace ble_gui::widgets {

class FluidParamsGraphWidget : public QWidget, private UI::FluidParams {
    Q_OBJECT

public:
    FluidParamsGraphWidget(QWidget* parent = nullptr);
    ~FluidParamsGraphWidget() { delete ui; }

    void update_view(const std::shared_ptr<ble_src::common::models::PhysData> physData, double sc);

signals:
    std::shared_ptr<wmf::FluidParamsDto> get_data(const std::shared_ptr<ble_src::common::models::PhysData> physData, double sc);

private:
    UI::FluidParams* ui;
};

} // namespace ble_gui::widgets

#endif
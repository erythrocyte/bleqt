#ifndef BLE_GUI_WIDGETS_FLUIDPARAMSGRAPHWIDGET_H_
#define BLE_GUI_WIDGETS_FLUIDPARAMSGRAPHWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "models/fluidParamsDto.hpp"
#include "uis/ui_fluidParamsWidget.hpp"

namespace wmf = ble::gui::widgets::models;

namespace ble::gui::widgets {

class FluidParamsGraphWidget : public QWidget, private UI::FluidParams {
    Q_OBJECT
public:
    FluidParamsGraphWidget(QWidget* parent = nullptr);
    ~FluidParamsGraphWidget() { delete ui; }

    void update_view(double n, double kmu, double sc);

signals:
    std::shared_ptr<wmf::FluidParamsDto> get_data(double n, double kmu, double sc);

private:
    UI::FluidParams* ui;

    void subscribe();

private slots:
    void handleImageSaveSvg();
};

} // namespace ble_gui::widgets

#endif
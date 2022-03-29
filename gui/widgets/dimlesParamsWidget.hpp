#ifndef BLE_GUI_WIDGETS_DIMLESPARAMSWIDGET_H_
#define BLE_GUI_WIDGETS_DIMLESPARAMSWIDGET_H_

#include <iostream>
#include <memory>
#include <string>

#include "models/dimlessParamsDto.hpp"
#include "uis/ui_dimlesParamsWidget.hpp"

namespace ble::gui::widgets {

class DimlesParamsWidget : public QWidget, private UI::DimlessParams {
    Q_OBJECT
public:
    DimlesParamsWidget(QWidget* parent = nullptr);
    ~DimlesParamsWidget() { delete ui; }

    void set_params(const std::shared_ptr<models::DimlessParamsDto> params);

private:
    UI::DimlessParams* ui;
};

} // namespace ble_gui::widgets

#endif

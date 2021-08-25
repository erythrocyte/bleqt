#ifndef BLEGUI_WIDGETS_WELLWORKDATAWIDGET_H_
#define BLEGUI_WIDGETS_WELLWORKDATAWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "calc/models/bleResultData.hpp"
#include "uis/ui_wellWorkDataWidget.hpp"

using namespace QtCharts;

namespace ble_gui::widgets {
class WellWorkDataWidget : public QWidget, private UI::WellWorkData {
    Q_OBJECT

public:
    WellWorkDataWidget(QWidget* parent = nullptr);
    ~WellWorkDataWidget() { delete ui; }

    void setData(const std::shared_ptr<ble_src::calc::models::BleResultData> data);

private:
    UI::WellWorkData* ui;
};

} // namespace ble_gui::widgets

#endif
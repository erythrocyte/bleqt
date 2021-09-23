/*
 * Filename: wellWorkDataWidget.hpp
 * Path: bleqt/gui/widgets
 * Created Date: Sunday, September 19th 2021, 10:46:09 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLEGUI_WIDGETS_WELLWORKDATAWIDGET_H_
#define BLEGUI_WIDGETS_WELLWORKDATAWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "common/models/wellWorkParams.hpp"
#include "uis/ui_wellWorkDataWidget.hpp"

using namespace QtCharts;

namespace ble_gui::widgets {
class WellWorkDataWidget : public QWidget, private UI::WellWorkData {
    Q_OBJECT

public:
    WellWorkDataWidget(QWidget* parent = nullptr);
    ~WellWorkDataWidget() { delete ui; }

    void setData(const std::vector<std::shared_ptr<ble_src::common::models::WellWorkParams>>& data);
    void set_xrange(double max_value);

private:
    UI::WellWorkData* ui;

    void subsribe();

private slots:
    void handleShowHideTable();
};

} // namespace ble_gui::widgets

#endif
/*
 * Filename: wellWorkDataWidget.hpp
 * Path: bleqt/gui/widgets
 * Created Date: Sunday, September 19th 2021, 10:46:09 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_WELLWORKDATAWIDGET_H_
#define BLE_GUI_WIDGETS_WELLWORKDATAWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "models/wellWorkParamsModel.hpp"
#include "uis/ui_wellWorkDataWidget.hpp"

using namespace QtCharts;

namespace ble::gui::widgets {
class WellWorkDataWidget : public QWidget, private UI::WellWorkData {
    Q_OBJECT

public:
    WellWorkDataWidget(QWidget* parent = nullptr);
    ~WellWorkDataWidget();

    void set_data(models::WellWorkParamsModel* model);
    void set_xrange(double max_value);

private:
    UI::WellWorkData* ui;
    models::WellWorkParamsModel* m_model;

    void subsribe();
    void fill_table();
    void fill_chart();

private slots:
    void handleShowHideTable();
};

} // namespace ble_gui::widgets

#endif
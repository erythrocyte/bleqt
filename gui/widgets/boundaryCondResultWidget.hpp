/*
 * Filename: boundaryCondResultWidget.hpp
 * Path: bleqt/gui/widgets
 * Created Date: Monday, September 27th 2021, 7:41:47 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_BOUNDARYCONDRESULTWIDGET_H_
#define BLE_GUI_WIDGETS_BOUNDARYCONDRESULTWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "models/topBotBoundModel.hpp"
#include "uis/ui_boundaryCondResultWidget.hpp"

using namespace QtCharts;

namespace ble::gui::widgets {
class TopBotBoundWidget : public QWidget, private UI::BoundaryCondResult {
    Q_OBJECT

public:
    TopBotBoundWidget(QWidget* parent = nullptr);
    ~TopBotBoundWidget();

    void set_data(models::TopBotBoundModel* model);
    void set_xrange(double max_value);

private:
    UI::BoundaryCondResult* ui;
    models::TopBotBoundModel* m_model;

    void subsribe();
    void fill_table();
    void fill_chart();

private slots:
    void handleShowHideTable();
};

} // namespace ble_gui::widgets

#endif

/*
 * Filename: boundaryCondResultWidget.hpp
 * Path: bleqt/gui/widgets
 * Created Date: Monday, September 27th 2021, 7:41:47 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_BOUNDVISUALWIDGET_H_
#define BLE_GUI_WIDGETS_BOUNDVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "models/boundModel.hpp"
#include "uis/ui_boundVisualWidget.hpp"

using namespace QtCharts;

namespace ble::gui::widgets {
class BoundVisualWidget : public QWidget, private UI::BoundVisual {
    Q_OBJECT

public:
    BoundVisualWidget(QWidget* parent = nullptr);
    ~BoundVisualWidget();

    void set_data(models::BoundModel* model);
    void set_xrange(double max_value);

private:
    UI::BoundVisual* ui;
    models::BoundModel* m_model;

    void subsribe();
    void fill_table();
    void fill_chart();

private slots:
    void handleShowHideTable();
};

} // namespace ble_gui::widgets

#endif

/*
 * Filename: tauVisualWidget.hpp
 * Path: bleqt/gui/widgets
 * Created Date: Friday, November 19th 2021, 8:20:38 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */


#ifndef BLE_GUI_WIDGETS_TAUVISUALWIDGET_H_
#define BLE_GUI_WIDGETS_TAUVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "models/tauModel.hpp"
#include "uis/ui_tauVisualWidget.hpp"

using namespace QtCharts;

namespace ble::gui::widgets {
class TauVisualWidget : public QWidget, private UI::TauVisual {
    Q_OBJECT

public:
    TauVisualWidget(QWidget* parent = nullptr);
    ~TauVisualWidget();

    void set_data(models::TauModel* model);
    void set_xrange(double max_value);

private:
    UI::TauVisual* ui;
    models::TauModel* m_model;

    void subsribe();
    void fill_table();
    void fill_chart();

private slots:
    void handleShowHideTable();
};

} // namespace ble_gui::widgets

#endif

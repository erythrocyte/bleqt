#ifndef BLE_GUI_WIDGETS_FWVISUALWIDGET_H_
#define BLE_GUI_WIDGETS_FWVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "models/fwModel.hpp"
#include "uis/ui_fwVisualWidget.hpp"

using namespace QtCharts;

namespace ble::gui::widgets {
class FwVisualWidget : public QWidget, private UI::FwVisual {
    Q_OBJECT

public:
    FwVisualWidget(QWidget* parent = nullptr);
    ~FwVisualWidget();

    void set_data(models::FwModel* model);
    void set_xrange(double max_value);

private:
    UI::FwVisual* ui;
    models::FwModel* m_model;

    void subsribe();
    void fill_table();
    void fill_chart();

private slots:
    void handleShowHideTable();
};

} // namespace ble_gui::widgets

#endif

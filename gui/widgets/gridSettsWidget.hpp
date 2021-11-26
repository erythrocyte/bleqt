#ifndef BLE_GUI_WIDGETS_GRIDSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_GRIDSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "common/models/meshSettings.hpp"
#include "uis/ui_gridSettsWidget.hpp"

namespace scm = ble::src::common::models;

namespace ble::gui::widgets {

class GridSettsWidget : public QWidget, private UI::GridSetts {
    Q_OBJECT
public:
    GridSettsWidget(QWidget* parent = nullptr);
    ~GridSettsWidget() { delete ui; }

    std::shared_ptr<scm::MeshSettings> get_data();

signals:
    void cell_count_changed();
    void grid_type_changed();

private:
    UI::GridSetts* ui;

    void subscribe();

private slots:
    void onCellCountChanged(int index) { emit cell_count_changed(); }
    void on_grid_type_changed(int index) { emit grid_type_changed(); }
};

} // namespace ble_gui::widgets

#endif
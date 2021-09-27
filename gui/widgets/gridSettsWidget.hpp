#ifndef BLE_GUI_WIDGETS_GRIDSETTSWIDGET_H_
#define BLE_GUI_WIDGETS_GRIDSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "uis/ui_gridSettsWidget.hpp"

#include "common/models/gridType.hpp"

namespace scm = ble::src::common::models;

namespace ble::gui::widgets {

class GridSettsWidget : public QWidget, private UI::GridSetts {
    Q_OBJECT
public:
    GridSettsWidget(QWidget* parent = nullptr);
    ~GridSettsWidget() { delete ui; }

    double getWellRadius() const { return ui->WellRadius->value(); }
    int getCellCount() const { return ui->CellCount->value(); }
    scm::GridType::TypeEnum get_grid_type();

signals:
    void cell_count_changed();

private:
    UI::GridSetts* ui;

    void subscribe();
    void fix_well_radius(const QString&);

private slots:
    void gridTypeChanged(int index);
    void onCellCountChanged(int index) { emit cell_count_changed(); }
};

} // namespace ble_gui::widgets

#endif
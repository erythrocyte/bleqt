#ifndef BLE_GUI_WIDGETS_PRESENTERS_GRIDSETTSWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_GRIDSETTSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "gridSettsWidget.hpp"

namespace ble::gui::widgets::presenters {

class GridSettsWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    GridSettsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<GridSettsWidget> view);
    ~GridSettsWidgetPresenter() { }

    std::shared_ptr<GridSettsWidget> get_view();

    double get_well_radius();
    int get_cell_count();

signals:
    void cellCountChanged();

private:
    void subscribe();

private slots:
    void onCellCountChanged() { emit cellCountChanged(); }
};

}

#endif
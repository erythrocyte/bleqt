#ifndef BLEGUI_WIDGETS_PRESENTERS_GRIDSETTSWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_GRIDSETTSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "gridSettsWidget.hpp"
#include "blePresenter.hpp"

namespace ble_gui::widgets::presenters {

class GridSettsWidgetPresenter : public mvp::BlePresenter {
public:
    GridSettsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<GridSettsWidget> view);
    ~GridSettsWidgetPresenter() {}

    std::shared_ptr<GridSettsWidget> get_view();

    double get_domain_len();
        int get_cell_count();
};

}

#endif
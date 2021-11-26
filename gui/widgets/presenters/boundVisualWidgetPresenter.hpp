#ifndef BLE_GUI_WIDGETS_PRESENTERS_BOUNDVISUALWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_BOUNDVISUALWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "boundVisualWidget.hpp"
#include "common/models/boundCondData.hpp"
#include "mesh/models/grid.hpp"
#include "models/boundModel.hpp"

namespace ble::gui::widgets::presenters {

class BoundVisualWidgetPresenter : public mvp::BlePresenter {
public:
    BoundVisualWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BoundVisualWidget> view);
    ~BoundVisualWidgetPresenter() { }

    void set_data(
        double x0, double x1, int n,
        const std::shared_ptr<src::common::models::BoundCondData>& data);

    std::shared_ptr<BoundVisualWidget> get_view();
};

}

#endif

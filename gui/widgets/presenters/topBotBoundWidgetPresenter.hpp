#ifndef BLE_GUI_WIDGETS_PRESENTERS_TOPBOTBOUNDWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_TOPBOTBOUNDWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "boundaryCondResultWidget.hpp"
#include "common/models/boundCondData.hpp"
#include "mesh/models/grid.hpp"
#include "models/topBotBoundModel.hpp"

namespace ble::gui::widgets::presenters {

class TopBotBoundWidgetPresenter : public mvp::BlePresenter {
public:
    TopBotBoundWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<TopBotBoundWidget> view);
    ~TopBotBoundWidgetPresenter() { }

    void set_data(
        const std::shared_ptr<src::mesh::models::Grid> grd,
        const std::shared_ptr<src::common::models::BoundCondData>& data);

    std::shared_ptr<TopBotBoundWidget> get_view();
};

}

#endif

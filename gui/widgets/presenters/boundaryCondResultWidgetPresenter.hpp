#ifndef BLE_GUI_WIDGETS_PRESENTERS_BOUNDARYCONDRESULTWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_BOUNDARYCONDRESULTWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "common/models/boundSourceCond.hpp"
#include "models/boundaryCondResultModel.hpp"
#include "boundaryCondResultWidget.hpp"
#include "mesh/models/grid.hpp"

namespace ble::gui::widgets::presenters {

class BoundaryCondResultWidgetPresenter : public mvp::BlePresenter {
public:
    BoundaryCondResultWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BoundaryCondResultWidget> view);
    ~BoundaryCondResultWidgetPresenter() { }

    void set_data(
        const std::shared_ptr<src::mesh::models::Grid> grd,
        const std::vector<std::shared_ptr<src::common::models::BoundSourceCond>>& data);

    std::shared_ptr<BoundaryCondResultWidget> get_view();
};

}

#endif

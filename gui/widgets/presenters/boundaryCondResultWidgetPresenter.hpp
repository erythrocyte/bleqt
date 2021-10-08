#ifndef BLE_GUI_WIDGETS_PRESENTERS_BOUNDARYCONDRESULTWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_BOUNDARYCONDRESULTWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "boundaryCondResultWidget.hpp"
#include "common/models/boundCondData.hpp"
#include "mesh/models/grid.hpp"
#include "models/boundaryCondResultModel.hpp"

namespace ble::gui::widgets::presenters {

class BoundaryCondResultWidgetPresenter : public mvp::BlePresenter {
public:
    BoundaryCondResultWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BoundaryCondResultWidget> view);
    ~BoundaryCondResultWidgetPresenter() { }

    void set_data(
        const std::shared_ptr<src::mesh::models::Grid> grd,
        const std::shared_ptr<src::common::models::BoundCondData>& data);

    std::shared_ptr<BoundaryCondResultWidget> get_view();
};

}

#endif

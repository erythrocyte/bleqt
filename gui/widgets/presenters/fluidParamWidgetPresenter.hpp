#ifndef BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "fluidParamsWidget.hpp"
#include "models/fluidParamsModel.hpp"
#include "physData.hpp"

namespace ble_gui::widgets::presenters {

class FluidParamWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    FluidParamWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<FluidParamsWidget> view);

    void update_view(const std::shared_ptr<ble_src::PhysData> physData, double sc);

private slots:
    std::shared_ptr<models::FluidParamsModel>
    send_data(const std::shared_ptr<ble_src::PhysData> data, double sc);
};

}

#endif
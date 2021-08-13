#ifndef BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMGRAPHWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMGRAPHWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "models/fluidParamsDto.hpp"
#include "common/models/physData.hpp"

namespace ble_gui::widgets::presenters {

class FluidParamGraphWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    FluidParamGraphWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<FluidParamsGraphWidget> view);
    ~FluidParamGraphWidgetPresenter() { }

    void update_view(const std::shared_ptr<ble_src::common::models::PhysData> physData, double sc);
    std::shared_ptr<FluidParamsGraphWidget> get_view();

private slots:
    std::shared_ptr<models::FluidParamsDto>
    send_data(const std::shared_ptr<ble_src::common::models::PhysData> data, double sc);
};

}

#endif

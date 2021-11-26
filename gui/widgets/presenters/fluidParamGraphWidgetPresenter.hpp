#ifndef BLE_GUI_WIDGETS_PRESENTERS_FLUIDPARAMGRAPHWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_FLUIDPARAMGRAPHWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "models/fluidParamsDto.hpp"

namespace ble::gui::widgets::presenters {

class FluidParamGraphWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    FluidParamGraphWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<FluidParamsGraphWidget> view);
    ~FluidParamGraphWidgetPresenter() { }

    void update_view(double n, double kmu, double sc);
    std::shared_ptr<FluidParamsGraphWidget> get_view();

private slots:
    std::shared_ptr<models::FluidParamsDto>
    send_data(double n, double kmu, double sc);
};

}

#endif

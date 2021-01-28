#ifndef BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "fluidParamsWidget.hpp"
#include "models/fluidParamsModel.hpp"
#include "physData.hpp"

namespace ble_gui::widgets::presenters {

class FluidParamWidgetPresenter : public QObject {
    Q_OBJECT
public:
    FluidParamWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<FluidParamsVisualWidget> view);

    std::shared_ptr<FluidParamsVisualWidget> get_view();
    void update_view(const std::shared_ptr<ble_src::PhysData> physData, double sc);

private:
    std::shared_ptr<Hypodermic::Container> m_container;
    std::shared_ptr<FluidParamsVisualWidget> m_view;

private slots:
    std::shared_ptr<models::FluidParamsModel>
    send_data(const std::shared_ptr<ble_src::PhysData> data, double sc);
};

}

#endif
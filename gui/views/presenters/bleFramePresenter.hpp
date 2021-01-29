#ifndef BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_
#define BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "bleFrame.hpp"
#include "widgets/presenters/fluidParamWidgetPresenter.hpp"

namespace ble_gui::views::presenters {
class BleFramePresenter : QObject {
    Q_OBJECT
private:
    std::shared_ptr<Hypodermic::Container> m_container;
    std::shared_ptr<BleFrame> m_view;
    std::shared_ptr<widgets::presenters::FluidParamWidgetPresenter> m_fluidVisualPresenter;

public:
    BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BleFrame> view);

    void run();

private slots:
    std::shared_ptr<widgets::FluidParamsWidget> get_fluid_widget() { return m_fluidVisualPresenter->get_view(); }
    void on_update_fluid_widget(
        const std::shared_ptr<ble_src::PhysData> physData, double sc);
};
}

#endif
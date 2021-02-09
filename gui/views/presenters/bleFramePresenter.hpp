#ifndef BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_
#define BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "bleFrame.hpp"

#include "widgets/presenters/dataWidgetPresenter.hpp"
#include "widgets/presenters/fluidParamWidgetPresenter.hpp"

namespace bwp = ble_gui::widgets::presenters;

namespace ble_gui::views::presenters {
class BleFramePresenter : QObject {
    Q_OBJECT
private:
    std::shared_ptr<Hypodermic::Container> m_container;
    std::shared_ptr<BleFrame> m_view;
    std::shared_ptr<bwp::FluidParamWidgetPresenter> m_fluidWidgetPresenter;
    std::shared_ptr<bwp::DataWidgetPresenter> m_dataWidgetPresenter;

public:
    BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BleFrame> view);

    void run();

private slots:
    void on_update_fluid_widget(
        const std::shared_ptr<ble_src::PhysData> physData, double sc);
};
}

#endif
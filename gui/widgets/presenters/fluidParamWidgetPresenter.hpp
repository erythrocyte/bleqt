#ifndef BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_FLUIDPARAMWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "fluidParamsWidget.hpp"
#include "models/fluidParamsModel.hpp"
#include "physData.hpp"

namespace ble_gui {
namespace widgets {
    namespace presenters {
        class FluidParamWidgetPresenter : public QObject {
        public:
            FluidParamWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
                std::shared_ptr<ble_gui::widgets::FluidParamsVisualWidget> view);

        private slots:
            std::shared_ptr<ble_gui::widgets::models::FluidParamsModel> send_data(const std::shared_ptr<ble_src::PhysData> data, double sc);
        };
    }
}
}

#endif
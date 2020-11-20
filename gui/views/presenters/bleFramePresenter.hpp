#ifndef BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_
#define BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "ibleFrame.hpp"
#include "widgets/presenters/fluidParamWidgetPresenter.hpp"

namespace ble_gui {
namespace views {
    namespace presenters {
        class BleFramePresenter {
        private:
            std::shared_ptr<Hypodermic::Container> m_container;
            std::shared_ptr<IBleFrame> m_view;
            std::shared_ptr<widgets::presenters::FluidParamWidgetPresenter> m_fluidVisualPresenter;

        public:
            BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
                std::shared_ptr<IBleFrame> view);

            void run();

        private slots:
            std::shared_ptr<widgets::FluidParamsVisualWidget> get_visual_widget() { return m_fluidVisualPresenter->get_view(); }
        };
    }
}
}

#endif
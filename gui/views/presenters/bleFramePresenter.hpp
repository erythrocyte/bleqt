#ifndef BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_
#define BLEGUI_VIEWS_PRESENTERS_BLEFRAMEPRESENTER_H_

#include "Hypodermic/Hypodermic.h"

#include "ibleFrame.hpp"

namespace ble_gui {
namespace views {
    namespace presenters {
        class BleFramePresenter {
        public:
            BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
                std::shared_ptr<IBleFrame> view);
        };
    }
}
}

#endif
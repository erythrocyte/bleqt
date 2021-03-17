#ifndef BLEGUI_WIDGETS_PRESENTERS_SHOCKFRONTSETTSWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_SHOCKFRONTSETTSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "shockFrontSettsWidget.hpp"

namespace ble_gui::widgets::presenters {

class ShockFrontSettsWidgetPresenter : public mvp::BlePresenter {
public:
    ShockFrontSettsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<ShockFrontSettsWidget> view);
    ~ShockFrontSettsWidgetPresenter() { }
};

}

#endif
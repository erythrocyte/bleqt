#ifndef BLEGUI_WIDGETS_PRESENTERS_SATURSOLVERSETTSWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_SATURSOLVERSETTSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "satSolverSettsWidget.hpp"

namespace ble_gui::widgets::presenters {

class SatSolverSettsWidgetPresenter : public mvp::BlePresenter {
public:
    SatSolverSettsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<SatSolverSettsWidget> view);
    ~SatSolverSettsWidgetPresenter() { }
};

}

#endif
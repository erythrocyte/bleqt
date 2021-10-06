#ifndef BLE_GUI_WIDGETS_PRESENTERS_SATURSOLVERSETTSWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_SATURSOLVERSETTSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "satSolverSettsWidget.hpp"

namespace ble::gui::widgets::presenters {

class SatSolverSettsWidgetPresenter : public mvp::BlePresenter {
public:
    SatSolverSettsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<SatSolverSettsWidget> view);
    ~SatSolverSettsWidgetPresenter() { }

    std::shared_ptr<SatSolverSettsWidget> get_view();
    double get_curant_value();
    double get_press_recalc_n();
    bool need_satur_solve();
};

}

#endif
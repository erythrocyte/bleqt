#ifndef BLEGUI_WIDGETS_PRESENTERS_RESULTDATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_RESULTDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "resultDataWidget.hpp"
#include "blePresenter.hpp"

namespace ble_gui::widgets::presenters {

class ResultDataWidgetPresenter : public mvp::BlePresenter {
public:
    ResultDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<ResultDataWidget> view);
    ~ResultDataWidgetPresenter() {}

    void update_sc(double l, double sc);
};

}

#endif

#ifndef BLEGUI_WIDGETS_PRESENTERS_RELPERMDATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_RELPERMDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "relPermDataWidget.hpp"

namespace ble_gui::widgets::presenters {

class RelPermDataWidgetPresenter : public mvp::BlePresenter {
public:
    RelPermDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<RelPermDataWidget> view);
    ~RelPermDataWidgetPresenter() { }
};

}

#endif
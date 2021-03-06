#ifndef BLEGUI_WIDGETS_PRESENTERS_MODELDATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_MODELDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "modelDataWidget.hpp"

namespace ble_gui::widgets::presenters {

class ModelDataWidgetPresenter : public mvp::BlePresenter {
public:
    ModelDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<ModelDataWidget> view);
    ~ModelDataWidgetPresenter() { }
};

}

#endif
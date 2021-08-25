#ifndef BLEGUI_WIDGETS_PRESENTERS_WELLWORKDATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_WELLWORKDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "wellWorkDataWidget.hpp"
#include "blePresenter.hpp"

namespace ble_gui::widgets::presenters {

class WellWorkDataWidgetPresenter : public mvp::BlePresenter {
public:
    WellWorkDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<WellWorkDataWidget> view);
    ~WellWorkDataWidgetPresenter() {}

    void set_data(const std::shared_ptr<ble_src::calc::models::BleResultData> data);
    
    std::shared_ptr<WellWorkDataWidget> get_view();
};

}

#endif

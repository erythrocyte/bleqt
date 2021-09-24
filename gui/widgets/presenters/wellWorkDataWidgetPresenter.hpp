#ifndef BLE_GUI_WIDGETS_PRESENTERS_WELLWORKDATAWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_WELLWORKDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "common/models/wellWorkParams.hpp"
#include "models/wellWorkParamsModel.hpp"
#include "wellWorkDataWidget.hpp"

namespace ble::gui::widgets::presenters {

class WellWorkDataWidgetPresenter : public mvp::BlePresenter {
public:
    WellWorkDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<WellWorkDataWidget> view);
    ~WellWorkDataWidgetPresenter() { }

    void set_data(const std::vector<std::shared_ptr<ble::src::common::models::WellWorkParams>>& data);
    void set_time_period(double value);

    std::shared_ptr<WellWorkDataWidget> get_view();
};

}

#endif

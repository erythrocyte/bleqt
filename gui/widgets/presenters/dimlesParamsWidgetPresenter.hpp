#ifndef BLE_GUI_WIDGETS_PRESENTERS_DIMLESPARAMSWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_DIMLESPARAMSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "dimlesParamsWidget.hpp"

namespace ble::gui::widgets::presenters {

class DimlesParamsWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    DimlesParamsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<DimlesParamsWidget> view);
    ~DimlesParamsWidgetPresenter() { }

    std::shared_ptr<DimlesParamsWidget> get_view();
    void set_m_value(double value);
};

}

#endif
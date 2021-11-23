#ifndef BLE_GUI_WIDGETS_PRESENTERS_GEOLOGYDATAWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_GEOLOGYDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "geologyDataWidget.hpp"

namespace ble::gui::widgets::presenters {

class GeologyDataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    GeologyDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<GeologyDataWidget> view);
    ~GeologyDataWidgetPresenter() { }

    std::shared_ptr<GeologyDataWidget> get_view();

    double get_k();
    double get_kf();
    double get_mf();

private:
    void subscribe();
};

}

#endif
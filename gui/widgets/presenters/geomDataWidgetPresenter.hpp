#ifndef BLE_GUI_WIDGETS_PRESENTERS_GEOMDATAWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_GEOMDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "geomDataWidget.hpp"

namespace ble::gui::widgets::presenters {

class GeomDataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    GeomDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<GeomDataWidget> view);
    ~GeomDataWidgetPresenter() { }

    std::shared_ptr<GeomDataWidget> get_view();

    double get_rw();
    double get_l();
    double get_r();
    double get_delta();

private:
    void subscribe();
};

}

#endif
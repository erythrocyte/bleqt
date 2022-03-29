#ifndef BLE_GUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "common/models/data.hpp"
#include "dataWidget.hpp"

namespace ble::gui::widgets::presenters {

class DataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    DataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<DataWidget> view);

    std::shared_ptr<ble::src::common::models::Data> get_data();
    std::shared_ptr<DataWidget> get_view();

signals:
    void rpValuesUpdated();
    void dimless_params_updated();

private:
    void set_signals();

private slots:
    void onRpValuesChanged() { emit rpValuesUpdated(); }
    void on_dimless_params_changed() {emit dimless_params_updated();}
};

}

#endif
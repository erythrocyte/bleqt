#ifndef BLE_GUI_WIDGETS_PRESENTERS_TAUVISUALWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_TAUVISUALWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "common/models/tauData.hpp"
#include "models/tauModel.hpp"
#include "tauVisualWidget.hpp"

namespace ble::gui::widgets::presenters {

class TauVisualWidgetPresenter : public mvp::BlePresenter {
public:
    TauVisualWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<TauVisualWidget> view);
    ~TauVisualWidgetPresenter() { }

    void set_data(const std::vector<std::shared_ptr<src::common::models::TauData>>& data);

    std::shared_ptr<TauVisualWidget> get_view();
};

}

#endif

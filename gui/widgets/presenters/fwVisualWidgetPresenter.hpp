#ifndef BLE_GUI_WIDGETS_PRESENTERS_FWVISUALWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_FWVISUALWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "common/models/fwData.hpp"
#include "fwVisualWidget.hpp"
#include "models/fwModel.hpp"

namespace ble::gui::widgets::presenters {

class FwVisualWidgetPresenter : public mvp::BlePresenter {
public:
    FwVisualWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<FwVisualWidget> view);
    ~FwVisualWidgetPresenter();

    void set_data(const std::vector<std::shared_ptr<src::common::models::FwData>>& data);
    std::shared_ptr<FwVisualWidget> get_view();

private:
    models::FwModel* m_model;

};

}

#endif

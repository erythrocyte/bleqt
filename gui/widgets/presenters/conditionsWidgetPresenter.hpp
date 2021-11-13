#ifndef BLE_GUI_WIDGETS_PRESENTERS_CONDITIONSWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_CONDITIONSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "conditionsWidget.hpp"
#include "common/models/boundCondData.hpp"

namespace ble::gui::widgets::presenters {

class ConditionsWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    ConditionsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<ConditionsWidget> view);
    ~ConditionsWidgetPresenter() { }

    std::shared_ptr<ConditionsWidget> get_view();
    std::shared_ptr<src::common::models::BoundCondData> get_bound_data(double x0, double x1);

signals:
    void rhsUpdate();

private:
    void subscribe();

private slots:
    void onRhsUpdate() { emit rhsUpdate(); }
};

}

#endif

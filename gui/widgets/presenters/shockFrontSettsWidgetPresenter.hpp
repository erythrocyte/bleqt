#ifndef BLE_GUI_WIDGETS_PRESENTERS_SHOCKFRONTSETTSWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_SHOCKFRONTSETTSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "shockFrontSettsWidget.hpp"

namespace ble::gui::widgets::presenters {

class ShockFrontSettsWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    ShockFrontSettsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<ShockFrontSettsWidget> view);
    ~ShockFrontSettsWidgetPresenter() { }

    std::shared_ptr<ShockFrontSettsWidget> get_view();
    void set_show_shockfront_status(bool status);
    void set_shockfront_value(double value);

signals:
    void showShockFrontCurve(bool status);

private:
    void set_signals();

private slots:
    void onShowShockFrontCurve(bool status) { emit showShockFrontCurve(status); }
};

}

#endif
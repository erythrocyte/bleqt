#ifndef BLE_GUI_WIDGETS_PRESENTERS_RELPERMDATAWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_RELPERMDATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "relPermDataWidget.hpp"

namespace ble::gui::widgets::presenters {

class RelPermDataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    RelPermDataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<RelPermDataWidget> view);
    ~RelPermDataWidgetPresenter() { }

    double get_kmu();
    double get_n();

    std::shared_ptr<RelPermDataWidget> get_view();

signals:
    void valuesChanged();

private:
    void set_signals();

private slots:
    void onValuesChanged() { emit valuesChanged(); }
};

}

#endif
#ifndef BLE_GUI_WIDGETS_PRESENTERS_BOUNDARYCONDITIONSWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_BOUNDARYCONDITIONSWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "boundaryConditionsWidget.hpp"

namespace ble::gui::widgets::presenters {

class BoundaryConditionsWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    BoundaryConditionsWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<BoundaryConditionsWidget> view);
    ~BoundaryConditionsWidgetPresenter() { }

    std::shared_ptr<BoundaryConditionsWidget> get_view();

signals:
    void rhsUpdate();

private:
    void subscribe();

private slots:
    void onRhsUpdate() { emit rhsUpdate(); }
};

}

#endif

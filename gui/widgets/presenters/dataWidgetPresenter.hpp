#ifndef BLEGUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "dataWidget.hpp"
#include "gridSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

class DataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    DataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<DataWidget> view);

private:
    std::shared_ptr<GridSettsWidgetPresenter> m_gridset_presenter;
    // std::shared_ptr<ModelDataWidget> m_modeldata_widget;

    void set_widgets_to_view();
    void resolve_sub_presenters();
};

}

#endif
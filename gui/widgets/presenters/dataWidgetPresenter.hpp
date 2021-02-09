#ifndef BLEGUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "dataWidget.hpp"

namespace ble_gui::widgets::presenters {

class DataWidgetPresenter : public QObject {
    Q_OBJECT
public:
    DataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<DataWidget> view);

    std::shared_ptr<DataWidget> get_view();

private:
    std::shared_ptr<Hypodermic::Container> m_container;
    std::shared_ptr<DataWidget> m_view;

    // std::shared_ptr<ModelDataWidget> m_modeldata_widget;

    // void set_widgets_to_view(std::shared_ptr<Hypodermic::Container> container);
};

}

#endif
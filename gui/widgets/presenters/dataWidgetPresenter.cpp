#include "dataWidgetPresenter.hpp"

#include <memory>

namespace ble_gui::widgets::presenters {

DataWidgetPresenter::DataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DataWidget> view)
    : BleWidgetPresenter(container, view)
{
    // set_widgets_to_view(container);
}

// void DataWidgetPresenter::set_widgets_to_view(std::shared_ptr<Hypodermic::Container> container)
// {
//     m_modeldata_widget = std::make_shared<ble_gui::widgets::ModelDataWidget>();
//     m_view->set_view_objects(m_modeldata_widget);
// }

}
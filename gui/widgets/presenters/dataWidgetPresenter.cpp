#include "dataWidgetPresenter.hpp"

#include <memory>

namespace ble_gui::widgets::presenters {

DataWidgetPresenter::DataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DataWidget> view)
    : BleWidgetPresenter(container, view)
{
    // m_container = container;
    // m_view = view;

    // set_widgets_to_view(container);
}

// std::shared_ptr<ble_gui::widgets::DataWidget> DataWidgetPresenter::get_view()
// {
//     return m_view;
// }

// void DataWidgetPresenter::set_widgets_to_view(std::shared_ptr<Hypodermic::Container> container)
// {
//     m_modeldata_widget = std::make_shared<ble_gui::widgets::ModelDataWidget>();
//     m_view->set_view_objects(m_modeldata_widget);
// }

}
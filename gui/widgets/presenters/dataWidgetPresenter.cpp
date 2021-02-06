#include "dataWidgetPresenter.hpp"

#include <memory>

namespace ble_gui::widgets::presenters {

DataWidgetPresenter::DataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DataWidget> view)
{
    m_container = container;
    m_view = view;
}

std::shared_ptr<ble_gui::widgets::DataWidget> DataWidgetPresenter::get_view()
{
    return m_view;
}

void DataWidgetPresenter::set_widgets_to_view(std::shared_ptr<Hypodermic::Container> container)
{
    
}

}
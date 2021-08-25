#include "wellWorkDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

WellWorkDataWidgetPresenter::WellWorkDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<WellWorkDataWidget> view)
    : BlePresenter(container, view)
{
}

void WellWorkDataWidgetPresenter::set_data(const std::shared_ptr<ble_src::calc::models::BleResultData> data)
{
    get_view()->setData(data);
}

std::shared_ptr<WellWorkDataWidget> WellWorkDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<WellWorkDataWidget>(m_view);
}

}

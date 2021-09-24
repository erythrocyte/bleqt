#include "wellWorkDataWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

WellWorkDataWidgetPresenter::WellWorkDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<WellWorkDataWidget> view)
    : BlePresenter(container, view)
{
}

void WellWorkDataWidgetPresenter::set_data(const std::vector<std::shared_ptr<ble_src::common::models::WellWorkParams>>& data)
{
    models::WellWorkParamsModel* model = new models::WellWorkParamsModel(data);
    get_view()->set_data(model);
}

std::shared_ptr<WellWorkDataWidget> WellWorkDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<WellWorkDataWidget>(m_view);
}

void WellWorkDataWidgetPresenter::set_time_period(double value)
{
    get_view()->set_xrange(value);
}

}

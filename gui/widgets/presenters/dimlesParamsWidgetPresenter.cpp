#include "dimlesParamsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

DimlesParamsWidgetPresenter::DimlesParamsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DimlesParamsWidget> view)
    : BlePresenter(container, view)
{
}

std::shared_ptr<DimlesParamsWidget> DimlesParamsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<DimlesParamsWidget>(m_view);
}

void DimlesParamsWidgetPresenter::set_m_value(double value)
{
     get_view()->set_mvalue(value);
}

}
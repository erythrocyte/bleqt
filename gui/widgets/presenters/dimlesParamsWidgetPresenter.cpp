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

void DimlesParamsWidgetPresenter::set_params(const std::shared_ptr<models::DimlessParamsDto> params)
{
    get_view()->set_params(params);
}

}
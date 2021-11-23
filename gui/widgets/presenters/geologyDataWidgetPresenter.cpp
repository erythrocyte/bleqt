#include "geologyDataWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

GeologyDataWidgetPresenter::GeologyDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<GeologyDataWidget> view)
    : BlePresenter(container, view)
{
    subscribe();
}

std::shared_ptr<GeologyDataWidget> GeologyDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<GeologyDataWidget>(m_view);
}

double GeologyDataWidgetPresenter::get_k()
{
    return get_view()->get_k();
}

double GeologyDataWidgetPresenter::get_kf()
{
    return get_view()->get_kf();
}

double GeologyDataWidgetPresenter::get_mf()
{
    return get_view()->get_mf();
}

void GeologyDataWidgetPresenter::subscribe()
{
}

}

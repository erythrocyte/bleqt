#include "geomDataWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

GeomDataWidgetPresenter::GeomDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<GeomDataWidget> view)
    : BlePresenter(container, view)
{
    subscribe();
}

std::shared_ptr<GeomDataWidget> GeomDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<GeomDataWidget>(m_view);
}

double GeomDataWidgetPresenter::get_rw()
{
    return get_view()->get_rw();
}

double GeomDataWidgetPresenter::get_l()
{
    return get_view()->get_l();
}

double GeomDataWidgetPresenter::get_r()
{
    return get_view()->get_r();
}

double GeomDataWidgetPresenter::get_delta()
{
    return get_view()->get_delta();
}

void GeomDataWidgetPresenter::subscribe()
{
}

}

#include "relPermDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

RelPermDataWidgetPresenter ::RelPermDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<RelPermDataWidget> view)
    : BlePresenter(container, view)
{
}

double RelPermDataWidgetPresenter::get_kmu()
{
    return get_view()->getKmu();
}

double RelPermDataWidgetPresenter::get_nwat()
{
    return get_view()->getNwat();
}

double RelPermDataWidgetPresenter::get_noil()
{
    return get_view()->getNoil();
}

std::shared_ptr<RelPermDataWidget> RelPermDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<RelPermDataWidget>(m_view);
}

}

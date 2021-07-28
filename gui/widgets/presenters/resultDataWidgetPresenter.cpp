#include "resultDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

ResultDataWidgetPresenter::ResultDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<ResultDataWidget> view)
    : BlePresenter(container, view)
{
}

void ResultDataWidgetPresenter::update_sc(double l, double sc)
{
    get_view()->update_sc_series(l, sc);
}

std::shared_ptr<ResultDataWidget> ResultDataWidgetPresenter::get_view()
{
    return  std::static_pointer_cast<ResultDataWidget>(m_view);
}

void ResultDataWidgetPresenter::set_sc_visibility(bool state)
{
    get_view()->set_sc_visible(state);
}

}

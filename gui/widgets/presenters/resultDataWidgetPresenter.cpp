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
    std::static_pointer_cast<widgets::ResultDataWidget>(m_view)->update_sc_series(l, sc);
}

}
#include "resultDataWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

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
    return std::static_pointer_cast<ResultDataWidget>(m_view);
}

void ResultDataWidgetPresenter::set_sc_visibility(bool state)
{
    get_view()->set_sc_visible(state);
}

void ResultDataWidgetPresenter::set_data(const std::shared_ptr<ble_src::calc::models::BleResultData> data,
    std::function<void(double)> progress)
{
    get_view()->setData(data, progress);
}

}

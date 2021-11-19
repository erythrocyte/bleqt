#include "tauVisualWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

TauVisualWidgetPresenter::TauVisualWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<TauVisualWidget> view)
    : BlePresenter(container, view)
{
}

void TauVisualWidgetPresenter::set_data(const std::vector<std::shared_ptr<src::common::models::TauData>>& data)
{
    models::TauModel* model = new models::TauModel(data);
    get_view()->set_data(model);
}

std::shared_ptr<TauVisualWidget> TauVisualWidgetPresenter::get_view()
{
    return std::static_pointer_cast<TauVisualWidget>(m_view);
}

}

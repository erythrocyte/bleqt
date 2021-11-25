#include "boundVisualWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

BoundVisualWidgetPresenter::BoundVisualWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BoundVisualWidget> view)
    : BlePresenter(container, view)
{
}

void BoundVisualWidgetPresenter::set_data(double x0, double x1, int n,
const std::shared_ptr<ble::src::common::models::BoundCondData>& data)
{
    models::BoundModel* model = new models::BoundModel(x0, x1, n, data);
    get_view()->set_data(model);
}

std::shared_ptr<BoundVisualWidget> BoundVisualWidgetPresenter::get_view()
{
    return std::static_pointer_cast<BoundVisualWidget>(m_view);
}

}

#include "topBotBoundWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

TopBotBoundWidgetPresenter::TopBotBoundWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<TopBotBoundWidget> view)
    : BlePresenter(container, view)
{
}

void TopBotBoundWidgetPresenter::set_data(
    const std::shared_ptr<src::mesh::models::Grid> grd,
    const std::shared_ptr<ble::src::common::models::BoundCondData>& data)
{
    models::TopBotBoundModel* model = new models::TopBotBoundModel(grd, data);
    get_view()->set_data(model);
}

std::shared_ptr<TopBotBoundWidget> TopBotBoundWidgetPresenter::get_view()
{
    return std::static_pointer_cast<TopBotBoundWidget>(m_view);
}

}

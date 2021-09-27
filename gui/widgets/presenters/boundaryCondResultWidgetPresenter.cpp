#include "boundaryCondResultWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

BoundaryCondResultWidgetPresenter::BoundaryCondResultWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BoundaryCondResultWidget> view)
    : BlePresenter(container, view)
{
}

void BoundaryCondResultWidgetPresenter::set_data(
    const std::shared_ptr<src::mesh::models::Grid> grd,
    const std::vector<std::shared_ptr<ble::src::common::models::BoundSourceCond>>& data)
{
    models::BoundaryCondResultModel* model = new models::BoundaryCondResultModel(grd, data);
    get_view()->set_data(model);
}

std::shared_ptr<BoundaryCondResultWidget> BoundaryCondResultWidgetPresenter::get_view()
{
    return std::static_pointer_cast<BoundaryCondResultWidget>(m_view);
}

}

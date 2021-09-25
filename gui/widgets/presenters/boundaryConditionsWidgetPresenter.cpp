#include "boundaryConditionsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

BoundaryConditionsWidgetPresenter::BoundaryConditionsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BoundaryConditionsWidget> view)
    : BlePresenter(container, view)
{
}

std::shared_ptr<BoundaryConditionsWidget> BoundaryConditionsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<BoundaryConditionsWidget>(m_view);
}

}

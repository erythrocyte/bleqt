#include "gridSettsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

GridSettsWidgetPresenter::GridSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<GridSettsWidget> view)
    : BlePresenter(container, view)
{
}

std::shared_ptr<GridSettsWidget> GridSettsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<GridSettsWidget>(m_view);
}

double GridSettsWidgetPresenter::get_well_radius()
{
    return get_view()->getWellRadius();
}

int GridSettsWidgetPresenter::get_cell_count()
{
    return get_view()->getCellCount();
}

}

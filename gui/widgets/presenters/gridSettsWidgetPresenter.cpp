#include "gridSettsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

GridSettsWidgetPresenter::GridSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<GridSettsWidget> view)
    : BlePresenter(container, view)
{
    subscribe();
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

void GridSettsWidgetPresenter::subscribe()
{
    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());
    auto success = QObject::connect(view_obj, SIGNAL(cell_count_changed()), this, SLOT(onCellCountChanged()));
    Q_ASSERT(success);
}

src::common::models::GridType::TypeEnum GridSettsWidgetPresenter::get_grid_type()
{
    return get_view()->get_grid_type();
}

}

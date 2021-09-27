#include "boundaryConditionsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

BoundaryConditionsWidgetPresenter::BoundaryConditionsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BoundaryConditionsWidget> view)
    : BlePresenter(container, view)
{
    subscribe();
}

std::shared_ptr<BoundaryConditionsWidget> BoundaryConditionsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<BoundaryConditionsWidget>(m_view);
}

void BoundaryConditionsWidgetPresenter::subscribe()
{
    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());
    auto success = QObject::connect(view_obj, SIGNAL(rhs_updated()), this, SLOT(onRhsUpdate()));
    Q_ASSERT(success);
}

std::shared_ptr<src::common::models::BoundCondData> BoundaryConditionsWidgetPresenter::get_bound_data()
{
    return get_view()->get_bound_data();
}

}

#include "conditionsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

ConditionsWidgetPresenter::ConditionsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<ConditionsWidget> view)
    : BlePresenter(container, view)
{
    subscribe();
}

std::shared_ptr<ConditionsWidget> ConditionsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<ConditionsWidget>(m_view);
}

void ConditionsWidgetPresenter::subscribe()
{
    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());
    auto success = QObject::connect(view_obj, SIGNAL(rhs_updated()), this, SLOT(onRhsUpdate()));
    Q_ASSERT(success);
}

std::shared_ptr<src::common::models::BoundCondData> ConditionsWidgetPresenter::get_bound_data(double x0, double x1)
{
    return get_view()->get_bound_data(x0, x1);
}

}

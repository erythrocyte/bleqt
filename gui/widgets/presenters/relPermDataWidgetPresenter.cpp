#include "relPermDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

RelPermDataWidgetPresenter ::RelPermDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<RelPermDataWidget> view)
    : BlePresenter(container, view)
{
    set_signals();
}

double RelPermDataWidgetPresenter::get_kmu()
{
    return get_view()->getKmu();
}

double RelPermDataWidgetPresenter::get_n()
{
    return get_view()->getN();
}

std::shared_ptr<RelPermDataWidget> RelPermDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<RelPermDataWidget>(m_view);
}

void RelPermDataWidgetPresenter::set_signals()
{
    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());
    auto success = QObject::connect(view_obj, SIGNAL(valuesUpdated()), this, SLOT(onValuesChanged()));
    Q_ASSERT(success);
}

}

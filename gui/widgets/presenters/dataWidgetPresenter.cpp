#include "dataWidgetPresenter.hpp"

#include <memory>

namespace ble::gui::widgets::presenters {

DataWidgetPresenter::DataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DataWidget> view)
    : BlePresenter(container, view)
{
    set_signals();
}

void DataWidgetPresenter::set_signals()
{
    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());
    auto success = QObject::connect(view_obj, SIGNAL(on_rp_values_updated()),
        this, SLOT(onRpValuesChanged()));
    Q_ASSERT(success);

    success = QObject::connect(view_obj, SIGNAL(on_dimless_params_changed()),
        this, SLOT(on_dimless_params_changed()));
    Q_ASSERT(success);
}

std::shared_ptr<ble::src::common::models::Data> DataWidgetPresenter::get_data()
{
    return get_view()->get_data();
}

std::shared_ptr<DataWidget> DataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<DataWidget>(m_view);
}

}

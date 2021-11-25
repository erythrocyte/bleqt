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
    // auto success = QObject::connect(m_shockfront_presenter.get(), SIGNAL(showShockFrontCurve(bool)),
    //     this, SLOT(onShowShockFrontCurve(bool)));
    // Q_ASSERT(success);
    auto success = QObject::connect(view_obj, SIGNAL(rp_values_updated()),
        this, SLOT(onRpValuesChanged()));
    Q_ASSERT(success);
    // success = QObject::connect(m_cond_presenter.get(), SIGNAL(rhsUpdate()),
    //     this, SLOT(onUpdateRhs()));
    // Q_ASSERT(success);
    // success = QObject::connect(m_gridset_presenter.get(), SIGNAL(cellCountChanged()),
    //     this, SLOT(onCellCountChanged()));
    // Q_ASSERT(success);    
}

std::shared_ptr<ble::src::common::models::Data> DataWidgetPresenter::get_data()
{
    return get_view()->get_data();
}

std::shared_ptr<DataWidget> DataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<DataWidget>(m_view);
}

// void DataWidgetPresenter::set_show_shockfront_status(bool status)
// {
//     m_shockfront_presenter->set_show_shockfront_status(status);
// }

// void DataWidgetPresenter::set_shockfront_value(double value)
// {
//     m_shockfront_presenter->set_shockfront_value(value);
// }

// void DataWidgetPresenter::onUpdateShockFrontValue(double value)
// {
//     m_shockfront_presenter->set_shockfront_value(value);
// }

}

#include "shockFrontSettsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

ShockFrontSettsWidgetPresenter::ShockFrontSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<ShockFrontSettsWidget> view)
    : BlePresenter(container, view)
{
    set_signals();
}

void ShockFrontSettsWidgetPresenter::set_signals()
{
    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());

    auto success = QObject::connect(view_obj, SIGNAL(showShockFrontCurve(bool)), this, SLOT(onShowShockFrontCurve(bool)));
    Q_ASSERT(success);
}

std::shared_ptr<ShockFrontSettsWidget> ShockFrontSettsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<ShockFrontSettsWidget>(m_view);
}

void ShockFrontSettsWidgetPresenter::set_show_shockfront_status(bool status)
{
    get_view()->set_show_shockfront_status(status);
}

void ShockFrontSettsWidgetPresenter::set_shockfront_value(double value)
{
    get_view()->SetShockFrontValue(value);
}

void ShockFrontSettsWidgetPresenter::set_block(bool status)
{
    get_view()->set_block(status);
}

std::shared_ptr<src::common::models::ShockFrontSettings> ShockFrontSettsWidgetPresenter::get_data()
{
    return get_view()->get_data();
}

}

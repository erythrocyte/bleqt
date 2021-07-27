#include "shockFrontSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

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

}
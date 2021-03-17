#include "shockFrontSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

ShockFrontSettsWidgetPresenter::ShockFrontSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<ShockFrontSettsWidget> view)
    : BlePresenter(container, view)
{
}

}
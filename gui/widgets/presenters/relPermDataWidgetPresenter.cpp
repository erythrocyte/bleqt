#include "relPermDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

RelPermDataWidgetPresenter ::RelPermDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<RelPermDataWidget> view)
    : BlePresenter(container, view)
{
}

}

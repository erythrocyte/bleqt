#include "gridSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

GridSettsWidgetPresenter::GridSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<GridSettsWidget> view)
    : BlePresenter(container, view)
{
}

}
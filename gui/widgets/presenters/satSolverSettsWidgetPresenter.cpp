#include "satSolverSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

SatSolverSettsWidgetPresenter ::SatSolverSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<SatSolverSettsWidget> view)
    : BlePresenter(container, view)
{
}

}

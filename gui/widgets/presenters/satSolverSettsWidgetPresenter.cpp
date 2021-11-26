#include "satSolverSettsWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

SatSolverSettsWidgetPresenter ::SatSolverSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<SatSolverSettsWidget> view)
    : BlePresenter(container, view)
{
}

std::shared_ptr<SatSolverSettsWidget> SatSolverSettsWidgetPresenter::get_view()
{
    return std::static_pointer_cast<SatSolverSettsWidget>(m_view);
}

std::shared_ptr<src::calc::models::SaturSolverSetts> SatSolverSettsWidgetPresenter::get_data()
{
    return get_view()->get_data();
}

}

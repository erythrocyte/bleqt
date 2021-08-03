#include "satSolverSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

SatSolverSettsWidgetPresenter ::SatSolverSettsWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<SatSolverSettsWidget> view)
    : BlePresenter(container, view)
{
}

std::shared_ptr<SatSolverSettsWidget> SatSolverSettsWidgetPresenter::get_view()
{
    return  std::static_pointer_cast<SatSolverSettsWidget>(m_view);
}

double SatSolverSettsWidgetPresenter::get_curant_value()
{
    return get_view()->getCurantVal();
}

        double SatSolverSettsWidgetPresenter::get_press_recalc_n()
        {
            return get_view()->getPressRecalcN();
        }

}

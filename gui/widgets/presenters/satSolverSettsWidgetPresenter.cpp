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
    auto result = std::make_shared<src::calc::models::SaturSolverSetts>();
    auto view = get_view();

    result->cur_val = view->getCurantVal();
    result->need_satur_solve = view->need_satur_solve();
    result->pN = view->getPressRecalcN();
    result->type = view->solver_type();

    return result;
}

}

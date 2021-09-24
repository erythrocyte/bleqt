#include "modelDataWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

ModelDataWidgetPresenter::ModelDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<ModelDataWidget> view)
    : BlePresenter(container, view)
{
}

double ModelDataWidgetPresenter::get_modeling_period()
{
    return get_view()->getModelingPeriod();
}

double ModelDataWidgetPresenter::get_save_fields_step()
{
    return get_view()->get_save_fields_step();
}

std::shared_ptr<ModelDataWidget> ModelDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<ModelDataWidget>(m_view);
}

}

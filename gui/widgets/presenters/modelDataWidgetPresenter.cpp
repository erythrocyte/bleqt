#include "modelDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

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

std::shared_ptr<ModelDataWidget> ModelDataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<ModelDataWidget>(m_view);
}

}
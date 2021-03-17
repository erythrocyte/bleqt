#include "modelDataWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

ModelDataWidgetPresenter::ModelDataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<ModelDataWidget> view)
    : BlePresenter(container, view)
{
}

}
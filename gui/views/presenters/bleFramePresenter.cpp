#include "bleFramePresenter.hpp"

#include "widgets/presenters/fluidParamWidgetPresenter.hpp"

ble_gui::views::presenters::BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<IBleFrame> view)
{
    m_container = container;
    m_view = view;

    auto fluidVisualPresenter = m_container->resolve<ble_gui::widgets::presenters::FluidParamWidgetPresenter>();
    
    auto fluidVisual = fluidVisualPresenter->get_view();
    m_view->set_widgets(fluidVisual);
}

void ble_gui::views::presenters::BleFramePresenter::run()
{
    m_view->run();
}
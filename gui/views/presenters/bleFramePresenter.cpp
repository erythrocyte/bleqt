#include "bleFramePresenter.hpp"


ble_gui::views::presenters::BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<IBleFrame> view)
{
    m_container = container;
    m_view = view;

    QObject* view_obj = dynamic_cast<QObject*>(view.get());

    QObject::connect(view_obj,
        SIGNAL(on_get_visual_widget),
        this,
        SLOT(get_visual_widget));

    m_fluidVisualPresenter = m_container->resolve<ble_gui::widgets::presenters::FluidParamWidgetPresenter>();
    
    auto fluidVisual = m_fluidVisualPresenter->get_view();
    m_view->set_widgets(fluidVisual);
}

void ble_gui::views::presenters::BleFramePresenter::run()
{
    m_view->run();
}
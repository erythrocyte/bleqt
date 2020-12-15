#include "bleFramePresenter.hpp"

namespace ble_gui::views::presenters {

BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<IBleFrame> view)
{
    m_container = container;
    m_view = view;

    QObject* view_obj = dynamic_cast<QObject*>(view.get());

    QObject::connect(view_obj,
        SIGNAL(update_fluid_view(const std::shared_ptr<ble_src::PhysData>, double)),
        this,
        SLOT(on_update_fluid_widget));

    m_fluidVisualPresenter = m_container->resolve<ble_gui::widgets::presenters::FluidParamWidgetPresenter>();

    auto fluidVisual = m_fluidVisualPresenter->get_view();
    m_view->set_widgets(fluidVisual);
}

void BleFramePresenter::run()
{
    m_view->run();
}

void BleFramePresenter::on_update_fluid_widget(
    const std::shared_ptr<ble_src::PhysData> physData, double sc)
{
    m_fluidVisualPresenter->update_view(physData, sc);
}

}
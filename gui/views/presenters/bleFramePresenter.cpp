#include "bleFramePresenter.hpp"

#include "widgets/dataWidget.hpp"
#include "widgets/fluidParamsWidget.hpp"

namespace ble_gui::views::presenters {

BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BleFrame> view)
    : BlePresenter(container, view)
{
    QObject* view_obj = dynamic_cast<QObject*>(view.get());

    // auto success = QObject::connect(
    //     view_obj, SIGNAL(update_fluid_view(const std::shared_ptr<ble_src::PhysData>, double)),
    //     this, SLOT(on_update_fluid_widget(const std::shared_ptr<ble_src::PhysData>, double)));
    // Q_ASSERT(success);

    m_fluidWidgetPresenter = m_container->resolve<bwp::FluidParamWidgetPresenter>();
    auto fluidParamsWidget = std::static_pointer_cast<widgets::FluidParamsWidget>(m_fluidWidgetPresenter->get_view());

    m_resultDataWidgetPresenter = m_container->resolve<bwp::ResultDataWidgetPresenter>();
    auto resultDataWidget = std::static_pointer_cast<widgets::ResultDataWidget>(m_resultDataWidgetPresenter->get_view());

    // m_dataWidgetPresenter = m_container->resolve<bwp::DataWidgetPresenter>();
    // auto dataWidgetView = std::static_pointer_cast<widgets::DataWidget>(m_dataWidgetPresenter->get_view());

    std::static_pointer_cast<BleFrame>(m_view)->set_widgets(fluidParamsWidget, resultDataWidget);
}

void BleFramePresenter::run()
{
    std::static_pointer_cast<BleFrame>(m_view)->run();
}

void BleFramePresenter::on_update_fluid_widget(
    const std::shared_ptr<ble_src::PhysData> physData, double sc)
{
    m_fluidWidgetPresenter->update_view(physData, sc);
}

}
#include "bleFramePresenter.hpp"

#include "dataWidget.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "shockFront.hpp"

namespace ble_gui::views::presenters {

BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BleFrame> view)
    : BlePresenter(container, view)
{
    // QObject* view_obj = dynamic_cast<QObject*>(view.get());

    // auto success = QObject::connect(
    //     view_obj, SIGNAL(update_fluid_view(const std::shared_ptr<ble_src::PhysData>, double)),
    //     this, SLOT(on_update_fluid_widget(const std::shared_ptr<ble_src::PhysData>, double)));
    // Q_ASSERT(success);

    m_fluidWidgetPresenter = m_container->resolve<bwp::FluidParamGraphWidgetPresenter>();
    auto fluidParamsWidget = std::static_pointer_cast<widgets::FluidParamsGraphWidget>(m_fluidWidgetPresenter->get_view());

    m_resultDataWidgetPresenter = m_container->resolve<bwp::ResultDataWidgetPresenter>();
    auto resultDataWidget = std::static_pointer_cast<widgets::ResultDataWidget>(m_resultDataWidgetPresenter->get_view());

    m_dataWidgetPresenter = m_container->resolve<bwp::DataWidgetPresenter>();
    auto dataWidgetView = std::static_pointer_cast<widgets::DataWidget>(m_dataWidgetPresenter->get_view());

    std::static_pointer_cast<BleFrame>(m_view)->set_widgets(fluidParamsWidget, resultDataWidget, dataWidgetView);

    set_signals();
    m_dataWidgetPresenter->set_show_shockfront_status(true);
    onRpValuesUpdated();
}

void BleFramePresenter::run()
{
    std::static_pointer_cast<BleFrame>(m_view)->run();
}

void BleFramePresenter::set_signals()
{
    auto success = QObject::connect(m_dataWidgetPresenter.get(), SIGNAL(showShockFrontCurve(bool)),
        this, SLOT(onShowShockFrontCurve(bool)));
    Q_ASSERT(success);
    success = QObject::connect(m_dataWidgetPresenter.get(), SIGNAL(rpValuesUpdated()),
        this, SLOT(onRpValuesUpdated()));
    Q_ASSERT(success);
}

void BleFramePresenter::onShowShockFrontCurve(bool status)
{
    m_resultDataWidgetPresenter->set_sc_visibility(status);
    if (status) {
        auto data = m_dataWidgetPresenter->get_input_data();
        double sc = ble_src::get_shock_front(data->phys);
        m_resultDataWidgetPresenter->update_sc(data->grd->l, sc);
    }
}

void BleFramePresenter::onRpValuesUpdated()
{
    auto data = m_dataWidgetPresenter->get_input_data();
    double sc = ble_src::get_shock_front(data->phys);
    m_dataWidgetPresenter->set_shockfront_value(sc);
    m_resultDataWidgetPresenter->update_sc(data->grd->l, sc);
    m_fluidWidgetPresenter->update_view(data->phys, sc);
}

}
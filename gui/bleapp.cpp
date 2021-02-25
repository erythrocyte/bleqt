#include "bleapp.hpp"

#include <QApplication>
#include <QWidget>

#include "bleFrame.hpp"
#include "bleFramePresenter.hpp"
#include "fluidParamGraphWidgetPresenter.hpp"
#include "dataWidgetPresenter.hpp"
#include "resultDataWidgetPresenter.hpp"

namespace ble {

BleApplication::BleApplication()
{
    Hypodermic::ContainerBuilder builder;

    builder.registerType<ble_gui::views::BleFrame>();
    builder.registerType<ble_gui::views::presenters::BleFramePresenter>();
    builder.registerType<ble_gui::widgets::FluidParamsGraphWidget>();
    builder.registerType<ble_gui::widgets::presenters::FluidParamGraphWidgetPresenter>();
    builder.registerType<ble_gui::widgets::DataWidget>();
    builder.registerType<ble_gui::widgets::presenters::DataWidgetPresenter>();
    builder.registerType<ble_gui::widgets::ResultDataWidget>();
    builder.registerType<ble_gui::widgets::presenters::ResultDataWidgetPresenter>();

    m_container = builder.build();
}

BleApplication::~BleApplication()
{
}

void BleApplication::run(int argc, char** argv)
{
    QApplication qapp(argc, argv);

    auto mainPresenter = m_container->resolve<ble_gui::views::presenters::BleFramePresenter>();
    mainPresenter->run();

    qapp.exec();
}

}

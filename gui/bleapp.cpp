#include "bleapp.hpp"

#include <QApplication>
#include <QWidget>

#include "bleFrame.hpp"
#include "presenters/bleFramePresenter.hpp"
#include "widgets/presenters/fluidParamWidgetPresenter.hpp"
#include "widgets/presenters/dataWidgetPresenter.hpp"

namespace ble {

BleApplication::BleApplication()
{
    Hypodermic::ContainerBuilder builder;

    builder.registerType<ble_gui::views::BleFrame>();
    builder.registerType<ble_gui::views::presenters::BleFramePresenter>();
    builder.registerType<ble_gui::widgets::FluidParamsWidget>();
    builder.registerType<ble_gui::widgets::presenters::FluidParamWidgetPresenter>();
    builder.registerType<ble_gui::widgets::DataWidget>();
    builder.registerType<ble_gui::widgets::presenters::DataWidgetPresenter>();

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

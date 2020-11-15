#include "bleapp.hpp"

#include <QApplication>
#include <QWidget>

#include "bleFrame.hpp"
#include "presenters/bleFramePresenter.hpp"
#include "ibleFrame.hpp"

ble::BleApplication::BleApplication()
{
    Hypodermic::ContainerBuilder builder;

    builder.registerType<ble_gui::views::BleFrame>();
    // builder.registerType<ble_gui::views::presenters::BleFramePresenter>();

    m_container = builder.build();
}

ble::BleApplication::~BleApplication()
{
}

void ble::BleApplication::run(int argc, char** argv)
{
    QApplication qapp(argc, argv);

    auto mainWindow = m_container->resolve<ble_gui::views::BleFrame>();
    auto mainPresenter(new ble_gui::views::presenters::BleFramePresenter(m_container, mainWindow));

    qapp.exec();
}

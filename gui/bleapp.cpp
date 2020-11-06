#include "bleapp.hpp"

#include <QApplication>
#include <QWidget>

#include "bleFrame.hpp"

ble::BleApplication::BleApplication()
{
    Hypodermic::ContainerBuilder builder;

    builder.registerType<ble_gui::views::BleFrame>();

    m_container = builder.build();
}

ble::BleApplication::~BleApplication()
{
}

void ble::BleApplication::run(int argc, char** argv)
{
    QApplication qapp(argc, argv);

    auto mainWindow = m_container->resolve<ble_gui::views::BleFrame>();
    mainWindow->show();

    qapp.exec();
}

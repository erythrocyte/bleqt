#include "bleFrame.hpp"

#include <QApplication>

#include "qVerticalLabel.hpp"

namespace ble_gui::views {
BleFrame::BleFrame(QWidget* parent)
    : QMainWindow(parent)
    , ui(new UI::UI_BleFrame)
{
    ui->setupUI(this);

    setCentralWidget(ui->central);
    setWindowTitle("Ble Frame");
    this->setFixedSize(1100, 750);

    // status bar
    this->setStatusBar(ui->statusBar);

    // menu
    this->setMenuBar(ui->menuBar);
    connect(ui->quit, &QAction::triggered, qApp, QApplication::quit);
    connect(ui->runAction, SIGNAL(triggered()), this, SLOT(handleRunButton()));

    addDockWidget(Qt::LeftDockWidgetArea, ui->dockSettings);
    addDockWidget(Qt::BottomDockWidgetArea, ui->dockMessages);
}

void BleFrame::set_settings_widget(std::shared_ptr<widgets::DataWidget> dataWidget)
{
    QTabWidget* tabSettings = new QTabWidget();
    tabSettings->setTabPosition(QTabWidget::TabPosition::West);
    tabSettings->addTab(dataWidget.get(), "");

    frames::QVerticalLabel* tabSettingsLabel1 = new frames::QVerticalLabel("Main");
    tabSettingsLabel1->setStyleSheet("QLabel { color : #C0BBFE }");

    QTabBar* tabbar = tabSettings->tabBar();
    tabSettings->setTabText(0, "");
    tabbar->setTabButton(0, QTabBar::LeftSide, tabSettingsLabel1);

    ui->dockSettings->setWidget(tabSettings);
}

void BleFrame::set_widgets(
    std::shared_ptr<widgets::FluidParamsGraphWidget> fluidParamsWidget,
    std::shared_ptr<widgets::ResultDataWidget> resultDataWidget,
    std::shared_ptr<widgets::DataWidget> dataWidget)
{
    this->set_settings_widget(dataWidget);
    ui->tabs->addTab(resultDataWidget.get(), "Results");
    ui->tabs->addTab(fluidParamsWidget.get(), "Fluid params");
}

}

#include "bleFrame.hpp"

#include <QApplication>

#include "qVerticalLabel.hpp"
#include "workString.hpp"

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

    addDockWidget(Qt::BottomDockWidgetArea, ui->dockMessages);
    addDockWidget(Qt::LeftDockWidgetArea, ui->dockSettings);
    ui->dockMessages->setAllowedAreas(Qt::BottomDockWidgetArea);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    resizeDocks({ ui->dockMessages }, { 50 }, Qt::Vertical); // This is the hack
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

void BleFrame::add_log_message(std::string str, ble_src::logging::SeverityLevelEnum level)
{
    std::string color_name = "Black";
    switch (level) {
    case ble_src::logging::kError:
        color_name = "Red";
        break;
    default:
        break;
    }

    std::string mess = ble_src::string_format("<font color=\"%s\">%s</font>", color_name.c_str(), str.c_str());
    ui->messagePlainText->appendHtml(QString::fromStdString(mess));
}

}

#include "bleFrame.hpp"

#include <QApplication>

#include "common/services/workString.hpp"
#include "qVerticalLabel.hpp"

namespace ble::gui::views {
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
    ui->dockMessages->setAllowedAreas(Qt::BottomDockWidgetArea);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

    resizeDocks({ ui->dockMessages }, { 50 }, Qt::Vertical); // This is the hack
    resizeDocks({ ui->dockSettings }, { 100 }, Qt::Horizontal); // This is the hack
}

void BleFrame::set_settings_widget(const std::shared_ptr<models::SettingsWidgetsDto> widgets)
{
    QTabWidget* tabSettings = new QTabWidget();
    tabSettings->setTabPosition(QTabWidget::TabPosition::West);
    tabSettings->addTab(widgets->dataWidget.get(), "");
    tabSettings->addTab(widgets->conditionsWidget.get(), "");
    tabSettings->addTab(widgets->satsolver_widget.get(), "");
    tabSettings->addTab(widgets->gridsetts_widget.get(), "");
    tabSettings->addTab(widgets->shockfront_widget.get(), "");
    tabSettings->addTab(widgets->dimles_params_widget.get(), "");
    tabSettings->setMinimumWidth(330);
    QTabBar* tabbar = tabSettings->tabBar();

    // data widget caption
    frames::QVerticalLabel* label = new frames::QVerticalLabel("Data");
    label->setTextColor(QColor(0, 0, 0, 127));
    tabSettings->setTabText(0, "");
    tabbar->setTabButton(0, QTabBar::LeftSide, label);

    // conditions widget caption
    label = new frames::QVerticalLabel("Conditions");
    label->setTextColor(QColor(0, 100, 0, 127));
    tabSettings->setTabText(1, "");
    tabbar->setTabButton(1, QTabBar::LeftSide, label);

    // satsolver
    label = new frames::QVerticalLabel("Solver");
    label->setTextColor(QColor(100, 0, 0, 127));
    tabSettings->setTabText(2, "");
    tabbar->setTabButton(2, QTabBar::LeftSide, label);

    // mesh settings
    label = new frames::QVerticalLabel("Mesh");
    label->setTextColor(QColor(0, 0, 100, 127));
    tabSettings->setTabText(3, "");
    tabbar->setTabButton(3, QTabBar::LeftSide, label);

    // shock front
    label = new frames::QVerticalLabel("Shock front");
    label->setTextColor(QColor(0, 0, 50, 127));
    tabSettings->setTabText(4, "");
    tabbar->setTabButton(4, QTabBar::LeftSide, label);

    // dimless params
    label = new frames::QVerticalLabel("Info");
    label->setTextColor(QColor(0, 0, 50, 127));
    tabSettings->setTabText(4, "");
    tabbar->setTabButton(5, QTabBar::LeftSide, label);

    ui->dockSettings->setWidget(tabSettings);
}

void BleFrame::set_widgets(const std::shared_ptr<models::ViewWidgetsDto> widgets)
{
    auto setts_widgets = std::make_shared<models::SettingsWidgetsDto>();
    setts_widgets->conditionsWidget = widgets->conditionsWidget;
    setts_widgets->dataWidget = widgets->dataWidget;
    setts_widgets->satsolver_widget = widgets->satsolver_widget;
    setts_widgets->gridsetts_widget = widgets->gridsetts_widget;
    setts_widgets->shockfront_widget = widgets->shockfront_widget;
    setts_widgets->dimles_params_widget = widgets->dimles_params_widget;

    this->set_settings_widget(setts_widgets);

    ui->tabs->addTab(widgets->resultDataWidget.get(), "Results");
    ui->tabs->addTab(widgets->fluidParamsWidget.get(), "Fluid params");
    ui->tabs->addTab(widgets->wellWorkDataWidget.get(), "Well work");
    ui->tabs->addTab(widgets->condWidget.get(), "Conditions");
    ui->tabs->addTab(widgets->tauWidget.get(), "Tau");
    ui->tabs->addTab(widgets->fwWidget.get(), "Aver");
    ui->tabs->addTab(widgets->schemeWidget.get(), "Scheme");

    std::cout << "a = " << widgets->schemeWidget.get() << "\n";
}

void BleFrame::add_log_message(std::string str, ble::src::logging::SeverityLevelEnum level)
{
    std::string color_name = "Black";
    switch (level) {
    case ble::src::logging::kError:
        color_name = "Red";
        break;
    case ble::src::logging::kWarning:
        color_name = "Orange";
        break;
    default:
        break;
    }

    std::string mess = ble::src::common::services::string_format("<font color=\"%s\">%s</font>", color_name.c_str(), str.c_str());
    ui->messagePlainText->appendHtml(QString::fromStdString(mess));
}

}

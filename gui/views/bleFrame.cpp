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

void BleFrame::set_settings_widget(
    std::shared_ptr<widgets::DataWidget> dataWidget,
    std::shared_ptr<widgets::ConditionsWidget> conditionsWidget,
    std::shared_ptr<widgets::SatSolverSettsWidget> satsolver_widget)
{
    QTabWidget* tabSettings = new QTabWidget();
    tabSettings->setTabPosition(QTabWidget::TabPosition::West);
    tabSettings->addTab(dataWidget.get(), "");
    tabSettings->addTab(conditionsWidget.get(), "");
    tabSettings->addTab(satsolver_widget.get(), "");
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

    ui->dockSettings->setWidget(tabSettings);
}

void BleFrame::set_widgets(
    std::shared_ptr<widgets::DataWidget> dataWidget,
    std::shared_ptr<widgets::ConditionsWidget> conditionsWidget,
    std::shared_ptr<widgets::SatSolverSettsWidget> satsolver_widget,
    std::shared_ptr<widgets::FluidParamsGraphWidget> fluidParamsWidget,
    std::shared_ptr<widgets::ResultDataWidget> resultDataWidget,
    std::shared_ptr<widgets::WellWorkDataWidget> wellWorkDataWidget,
    std::shared_ptr<widgets::BoundVisualWidget> condWidget,
    std::shared_ptr<widgets::TauVisualWidget> tauWidget)
{
    this->set_settings_widget(dataWidget, conditionsWidget, satsolver_widget);
    ui->tabs->addTab(resultDataWidget.get(), "Results");
    ui->tabs->addTab(fluidParamsWidget.get(), "Fluid params");
    ui->tabs->addTab(wellWorkDataWidget.get(), "Well work");
    ui->tabs->addTab(condWidget.get(), "Conditions");
    ui->tabs->addTab(tauWidget.get(), "Tau");
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

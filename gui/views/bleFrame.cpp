#include "bleFrame.hpp"

#include <sstream>
#include <tuple>
#include <chrono>
#include <iomanip>

#include <QCoreApplication>
#include <QMenuBar>
#include <QApplication>
#include <QCommonStyle>
#include <QPen>

#include "makeGrid.hpp"
#include "pressureSolver.hpp"
#include "saturSolverNum.hpp"
#include "saturSolverType.hpp"
#include "workTimeStep.hpp"
#include "shockFront.hpp"
#include "saturSolverAnalytic.hpp"
#include "workParam.hpp"

#include "qVerticalLabel.hpp"

ble_gui::views::BleFrame::BleFrame(QWidget *parent)
	: QMainWindow(parent)
{
	_solver = std::make_shared<ble_src::BleCalc>();
	layout = new QGridLayout;

	central = new QWidget(this);
	central->setLayout(layout);

	setCentralWidget(central);
	setWindowTitle("Ble Frame");
	this->setFixedSize(1100, 750);

	this->set_settings_widget();
	this->set_visual_data_widget();
	this->set_menu();
	this->set_default_data();
	this->set_status_bar();
	this->set_signals();
}

ble_gui::views::BleFrame::~BleFrame()
{
}

void ble_gui::views::BleFrame::set_status_bar()
{
	statusBar = new QStatusBar();
	statusLabel = new QLabel(tr("Ready to run calculation"));
	statusBar->addWidget(statusLabel);
	statusProgressBar = new QProgressBar();
	statusProgressBar->setMaximum(100);
	statusBar->addWidget(statusProgressBar);

	this->setStatusBar(statusBar);
}

void ble_gui::views::BleFrame::set_menu()
{
	QCommonStyle *style = new QCommonStyle();
	QAction *quit = new QAction("&Quit", this);
	quit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));

	QMenu *file = menuBar()->addMenu("&File");
	file->addAction(quit);
	connect(quit, &QAction::triggered, qApp, QApplication::quit);

	menu = menuBar()->addMenu("&View");
	QAction *showSettings = _dock->toggleViewAction();
	showSettings->setIcon(style->standardIcon(QStyle::SP_FileDialogDetailedView));
	menu->addAction(showSettings);

	menu = menuBar()->addMenu("&Task");
	QAction *runAction = new QAction("Run");
	connect(runAction, SIGNAL(triggered()), this, SLOT(handleRunButton()));
	menu->addAction(runAction);
}

void ble_gui::views::BleFrame::set_settings_widget()
{
	QTabWidget *tabSettings = new QTabWidget();
	tabSettings->setTabPosition(QTabWidget::TabPosition::West);
	dataWidget = new widgets::DataWidget();
	tabSettings->addTab(dataWidget, "");

	frames::QVerticalLabel *tabSettingsLabel1 = new frames::QVerticalLabel("Main");
	tabSettingsLabel1->setStyleSheet("QLabel { color : #C0BBFE }");

	QTabBar *tabbar = tabSettings->tabBar();
	tabSettings->setTabText(0, "");
	tabbar->setTabButton(0, QTabBar::LeftSide, tabSettingsLabel1);

	_dock = new QDockWidget(tr("Settings"), this);
	_dock->setWidget(tabSettings);
	addDockWidget(Qt::LeftDockWidgetArea, _dock);
}

void ble_gui::views::BleFrame::set_visual_data_widget()
{
	QTabWidget *visDataWidget = new QTabWidget();
	resultDataVisual = new widgets::ResultDataVisualWidget();
	visDataWidget->addTab(resultDataVisual, "Results");

	fluidParamsVisual = new widgets::FluidParamsVisualWidget();
	visDataWidget->addTab(fluidParamsVisual, "Fluid params");

	layout->addWidget(visDataWidget, 0, 0);
}

void ble_gui::views::BleFrame::set_signals()
{
	connect(dataWidget->ShockFrontSetts->showCurve, SIGNAL(stateChanged(int)), this, SLOT(showScCheckedChange()));
	connect(dataWidget->PhysData->Noil, SIGNAL(valueChanged(double)), this, SLOT(update_static_visual()));
	connect(dataWidget->PhysData->Nwat, SIGNAL(valueChanged(double)), this, SLOT(update_static_visual()));
	connect(dataWidget->PhysData->Kmu, SIGNAL(valueChanged(double)), this, SLOT(update_static_visual()));
}

void ble_gui::views::BleFrame::showScCheckedChange()
{
	resultDataVisual->set_sc_visible(dataWidget->ShockFrontSetts->showCurve->isChecked());
}

void ble_gui::views::BleFrame::handleRunButton()
{
	auto start = std::chrono::high_resolution_clock::now();

	this->updateInputData();
	this->make_grid();

	statusLabel->setText(tr("calculation running"));

	std::function<void(int)> a = std::bind(&BleFrame::update_progress, this, std::placeholders::_1);

	_solver->calc(_grd, _data, a);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;

	std::ostringstream oss;
	oss << "calculation completed in " << std::fixed << std::setprecision(1) << diff.count() << " s.";
	statusLabel->setText(QString::fromStdString(oss.str()));

	std::shared_ptr<ble_src::BleResultData> results = _solver->get_result();
	results->grd = _grd;

	resultDataVisual->setData(results, a);
	statusLabel->setText(QString::fromStdString(oss.str()));
}

void ble_gui::views::BleFrame::update_progress(double perc)
{
	statusProgressBar->setValue(perc);
}

void ble_gui::views::BleFrame::set_default_data()
{
	_data = std::make_shared<ble_src::InputData>();
	_data->grd->type = ble_src::GridType::TypeEnum::kRegular;
	_data->satSetts->type == ble_src::SaturSolverType::kExplicit;

	updateInputData();
	update_static_visual();
}

void ble_gui::views::BleFrame::make_grid()
{
	_grd = ble_src::make_grid(_data);
}

void ble_gui::views::BleFrame::updateInputData()
{
	_data->model->period = dataWidget->ModelData->Period->value();

	_data->phys->kmu = dataWidget->PhysData->Kmu->value();
	_data->phys->n_oil = dataWidget->PhysData->Noil->value();
	_data->phys->n_wat = dataWidget->PhysData->Nwat->value();
	_data->phys->perm = dataWidget->PhysData->Perm->value();
	_data->phys->poro = dataWidget->PhysData->Poro->value();

	_data->satSetts->cur_val = dataWidget->SaturSolverSetts->Curant->value();
	_data->satSetts->pN = dataWidget->SaturSolverSetts->RecalcPressN->value();

	_data->grd->l = dataWidget->GridSetts->getLenght();
	_data->grd->n = dataWidget->GridSetts->getCellCount();
}

void ble_gui::views::BleFrame::update_static_visual()
{
	updateInputData();
	double sc = ble_src::get_shock_front(_data->phys);
	resultDataVisual->update_sc_series(_data->grd->l, sc);

	std::ostringstream oss;
	oss << "Shock front = " << std::fixed << std::setprecision(3) << sc;
	dataWidget->ShockFrontSetts->shockFrontValue->setText(QString::fromStdString(oss.str()));

	fluidParamsVisual->update_view(_data->phys, sc);
}
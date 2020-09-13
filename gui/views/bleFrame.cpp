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

void a(double c)
{
	std::cout << "progress = " << c << " %" << std::endl;
}

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

	set_settings_widget();

	set_visual_data_widget();

	set_menu();

	this->set_default_data();

	statusBar = new QStatusBar();
	statusLabel = new QLabel(tr("Ready to run calculation"));
	statusBar->addWidget(statusLabel);
	statusProgressBar = new QProgressBar();
	statusProgressBar->setMaximum(100);
	statusBar->addWidget(statusProgressBar);

	this->setStatusBar(statusBar);

	this->set_signals();
}

ble_gui::views::BleFrame::~BleFrame()
{
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

	layout->addWidget(visDataWidget, 0, 0);
}

void ble_gui::views::BleFrame::set_signals()
{

	connect(dataWidget->ShockFrontSetts->showCurve, SIGNAL(stateChanged(int)), this, SLOT(showScCheckedChange()));
	connect(dataWidget->PhysData->Noil, SIGNAL(valueChanged(double)), this, SLOT(update_sc()));
	connect(dataWidget->PhysData->Nwat, SIGNAL(valueChanged(double)), this, SLOT(update_sc()));
	connect(dataWidget->PhysData->Kmu, SIGNAL(valueChanged(double)), this, SLOT(update_sc()));
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

	statusLabel->setText(tr("chart series filling"));
	start = std::chrono::high_resolution_clock::now();
	std::shared_ptr<ble_src::BleResultData> results = _solver->get_result();

	int index = 0;
	size_t count = results->data.size();
	for (auto &d : results->data)
	{
		// this->fill_time_series(index == 0, d);
		double perc = std::min(100.0, ((double)index / count * 100.0));
		if (index % (count / 20) == 0)
			update_progress(perc);
		index++;
	}
	update_progress(100.0);

	end = std::chrono::high_resolution_clock::now();
	diff = end - start;

	oss.str("");
	oss << "charts completed in " << std::fixed << std::setprecision(1) << diff.count() << " s.";
	statusLabel->setText(QString::fromStdString(oss.str()));
}

void ble_gui::views::BleFrame::update_progress(double perc)
{
	statusProgressBar->setValue(perc);
}

void ble_gui::views::BleFrame::set_default_data()
{
	_data = std::make_shared<ble_src::InputData>();
	_data->phys->kmu = dataWidget->PhysData->Kmu->value();
	_data->phys->n_oil = dataWidget->PhysData->Noil->value();
	_data->phys->n_wat = dataWidget->PhysData->Nwat->value();
	_data->phys->poro = dataWidget->PhysData->Poro->value();
	_data->phys->perm = dataWidget->PhysData->Perm->value();

	_data->model->period = dataWidget->ModelData->Period->value();

	_data->grd->l = dataWidget->GridSetts->Length->value();
	_data->grd->n = dataWidget->GridSetts->CellCount->value();
	_data->grd->type = ble_src::GridType::TypeEnum::kRegular;

	_data->satSetts->cur_val = dataWidget->SaturSolverSetts->Curant->value();
	_data->satSetts->pN = dataWidget->SaturSolverSetts->RecalcPressN->value();
	_data->satSetts->type == ble_src::SaturSolverType::kExplicit;

	update_sc();	
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

	_data->grd->l = dataWidget->GridSetts->Length->value();
	_data->grd->n = dataWidget->GridSetts->CellCount->value();
}

void ble_gui::views::BleFrame::update_sc()
{
	updateInputData();
	double sc = ble_src::get_shock_front(_data->phys);
	resultDataVisual->update_sc_series(_data->grd->l, sc);

	std::ostringstream oss;
	oss << "Shock front = " << std::fixed << std::setprecision(3) << sc;
	dataWidget->ShockFrontSetts->shockFrontValue->setText(QString::fromStdString(oss.str()));
}
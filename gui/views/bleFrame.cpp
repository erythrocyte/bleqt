#include "bleFrame.hpp"

#include <sstream>
#include <tuple>
#include <chrono>
#include <iomanip>

#include <QCoreApplication>
#include <QDockWidget>
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

	slider = new QSlider(Qt::Orientation::Horizontal);
	layout->addWidget(slider, 1, 0, 1, 10);
	slider->setTickInterval(1.);
	slider->setMinimum(1);
	slider->setMaximum(1);
	slider->setValue(1);

	label = new QLabel();
	layout->addWidget(label, 1, 10);

	chart = new QChart();
	chart->legend()->setVisible(true);

	// Настройка осей графика
	axisX = new QValueAxis();
	axisX->setTitleText("x");
	axisX->setLabelFormat("%i");
	axisX->setTickCount(1);

	axisYSat = new QValueAxis();
	axisYSat->setTitleText("s / p");
	axisYSat->setLabelFormat("%g");
	axisYSat->setTickCount(5);
	axisYSat->setMin(0.);
	axisYSat->setMax(1.);

	chartView = new QChartView(chart);
	layout->addWidget(chartView, 0, 0, 1, 11);

	central = new QWidget(this);
	central->setLayout(layout);

	setCentralWidget(central);
	setWindowTitle("Ble Frame");
	this->setFixedSize(1100, 750);

	QCommonStyle *style = new QCommonStyle();
	QAction *quit = new QAction("&Quit", this);
	quit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));

	QMenu *file = menuBar()->addMenu("&File");
	file->addAction(quit);
	connect(quit, &QAction::triggered, qApp, QApplication::quit);

	QTabWidget *tabSettings = new QTabWidget();
	tabSettings->setTabPosition(QTabWidget::TabPosition::West);
	dataWidget = new widgets::DataWidget();
	tabSettings->addTab(dataWidget, "");

	frames::QVerticalLabel *tabSettingsLabel1 = new frames::QVerticalLabel("Main");
	tabSettingsLabel1->setStyleSheet("QLabel { color : #C0BBFE }");

	QTabBar *tabbar = tabSettings->tabBar();
	tabSettings->setTabText(0, "");
	tabbar->setTabButton(0, QTabBar::LeftSide, tabSettingsLabel1);

	QDockWidget *dock = new QDockWidget(tr("Settings"), this);
	dock->setWidget(tabSettings);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	menu = menuBar()->addMenu("&View");
	QAction *showSettings = dock->toggleViewAction();
	showSettings->setIcon(style->standardIcon(QStyle::SP_FileDialogDetailedView));
	menu->addAction(showSettings);

	menu = menuBar()->addMenu("&Task");
	QAction *runAction = new QAction("Run");
	connect(runAction, SIGNAL(triggered()), this, SLOT(handleRunButton()));
	menu->addAction(runAction);

	this->set_default_data();
	this->update_sc_series(true);

	statusBar = new QStatusBar();
	statusLabel = new QLabel(tr("Ready to run calculation"));
	statusBar->addWidget(statusLabel);
	statusProgressBar = new QProgressBar();
	statusProgressBar->setMaximum(100);
	statusBar->addWidget(statusProgressBar);

	this->setStatusBar(statusBar);

	series_press = new QLineSeries();
	series_press->setName("p");

	series_sat_num = new QLineSeries();
	series_sat_num->setName("s_num");

	series_sat_an = new QLineSeries();
	series_sat_an->setName("s_an");

	this->set_signals();
}

void ble_gui::views::BleFrame::set_signals()
{
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChange()));
	connect(dataWidget->ShockFrontSetts->showCurve, SIGNAL(stateChanged(int)), this, SLOT(showScCheckedChange()));
	connect(dataWidget->PhysData->Noil, SIGNAL(valueChanged(double)), this, SLOT(update_sc()));
	connect(dataWidget->PhysData->Nwat, SIGNAL(valueChanged(double)), this, SLOT(update_sc()));
	connect(dataWidget->PhysData->Kmu, SIGNAL(valueChanged(double)), this, SLOT(update_sc()));
}

void ble_gui::views::BleFrame::showScCheckedChange()
{
	if (dataWidget->ShockFrontSetts->showCurve->isChecked())
	{
		this->fill_sc_series();
	}
	else
	{
		chart->removeSeries(series_sc);
		series_sc->clear();
	}
}

void ble_gui::views::BleFrame::handleRunButton()
{
	auto start = std::chrono::high_resolution_clock::now();

	slider->setValue(1);
	label->setText("");

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
		this->fill_time_series(index == 0, d);
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

	slider->setMaximum(count);
	handleSliderValueChange();
}

ble_gui::views::BleFrame::~BleFrame()
{
}

void ble_gui::views::BleFrame::update_progress(double perc)
{
	statusProgressBar->setValue(perc);
}

void ble_gui::views::BleFrame::handleSliderValueChange()
{
	int value = slider->value() - 1;
	if (value < _solver->get_data_len())
	{
		update_time_info(value);
		fill_time_series(false, _solver->get_data(value));
	}
}

void ble_gui::views::BleFrame::update_time_info(int index)
{
	int count = _solver->get_data_len(); // resultData->data.size();
	std::ostringstream oss;
	oss << index + 1 << "/" << count;
	label->setText(QString::fromStdString(oss.str()));
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
}

void ble_gui::views::BleFrame::make_grid()
{
	_grd = ble_src::make_grid(_data);
}

void ble_gui::views::BleFrame::fill_time_series(bool init,
												const std::shared_ptr<ble_src::DynamicData> d)
{
	std::ostringstream oss;
	oss.str("");
	oss << "t = " << d->t;

	chart->setTitle(QString::fromStdString(oss.str()));

	if (!init)
	{
		chart->removeSeries(series_press);
		chart->removeSeries(series_sat_num);
		chart->removeSeries(series_sat_an);

		series_press->clear();
		series_sat_num->clear();
		series_sat_an->clear();
	}

	for (auto &cl : _grd->cells)
	{
		series_press->append(cl->cntr, d->p[cl->ind]);
		series_sat_num->append(cl->cntr, d->s[cl->ind]);
	}

	for (auto &v : d->s_an)
	{
		double x1, s1;
		std::tie(x1, s1) = v;
		series_sat_an->append(x1, s1);
	}

	chart->addSeries(series_press);
	chart->setAxisX(axisX, series_press);
	chart->setAxisY(axisYSat, series_press);

	chart->addSeries(series_sat_num);
	chart->setAxisX(axisX, series_sat_num);	   // obsolete
	chart->setAxisY(axisYSat, series_sat_num); // obsolete

	chart->addSeries(series_sat_an);
	chart->setAxisX(axisX, series_sat_an);	  // obsolete
	chart->setAxisY(axisYSat, series_sat_an); // obsolete
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

	this->update_sc_series(false);
}

void ble_gui::views::BleFrame::update_sc_series(bool init)
{
	if (init)
	{
		series_sc = new QLineSeries();
		QPen pen;
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);
		// pen.setBrush(Qt::green);
		series_sc->setPen(pen);
		series_sc->setName(tr("sc"));
	}
	else
	{
		chart->removeSeries(series_sc);
		series_sc->clear();
	}

	fill_sc_series();
}

void ble_gui::views::BleFrame::fill_sc_series()
{
	double sc = ble_src::get_shock_front(_data->phys);

	std::ostringstream oss;
	oss << "Shock front = " << std::fixed << std::setprecision(3) << sc;
	dataWidget->ShockFrontSetts->shockFrontValue->setText(QString::fromStdString(oss.str()));

	series_sc->append(0.0, sc);
	series_sc->append(_data->grd->l, sc);
	chart->addSeries(series_sc);
	chart->setAxisX(axisX, series_sc);
	chart->setAxisY(axisYSat, series_sc);
}

void ble_gui::views::BleFrame::update_sc()
{
	this->updateInputData();
	this->update_sc_series(false);
}

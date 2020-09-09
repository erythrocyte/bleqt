#include "bleFrame.hpp"

#include <sstream>

#include <QCoreApplication>
#include <QDockWidget>
#include <QMenuBar>
#include <QApplication>
#include <QCommonStyle>

#include "makeGrid.hpp"
#include "pressureSolver.hpp"
#include "saturSolver.hpp"
#include "saturSolverType.hpp"
#include "workTimeStep.hpp"
#include "shockFront.hpp"

namespace ble_gui{

BleFrame::BleFrame(QWidget* parent)
	: QMainWindow(parent)
{
	layout = new QGridLayout;

	slider = new QSlider(Qt::Orientation::Horizontal);
	layout->addWidget(slider, 1, 0, 1, 10);

	label = new QLabel();
	layout->addWidget(label, 1, 10);

	chart = new QChart();
	
	// Настройка осей графика
	axisX = new QValueAxis();
	axisX->setTitleText("x");
	axisX->setLabelFormat("%i");
	axisX->setTickCount(1);

	axisYPress = new QValueAxis();
	axisYPress->setTitleText("p");
	axisYPress->setLabelFormat("%g");
	axisYPress->setTickCount(5);
	axisYPress->setMin(0.);
	axisYPress->setMax(1.);

	axisYSat = new QValueAxis();
	axisYSat->setTitleText("s");
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
	this->setFixedSize(600, 400);

	QCommonStyle* style = new QCommonStyle();
	QAction *quit = new QAction("&Quit", this);
	quit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));

	QMenu *file = menuBar()->addMenu("&File");
	file->addAction(quit);
	connect(quit, &QAction::triggered, qApp, QApplication::quit);

	dataWidget = new DataWidget();

	QDockWidget *dock = new QDockWidget(tr("Settings"), this);
	dock->setWidget(dataWidget);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	menu = menuBar()->addMenu("&View");
	QAction* showSettings = dock->toggleViewAction();
	showSettings->setIcon(style->standardIcon(QStyle::SP_FileDialogDetailedView));
	menu->addAction(showSettings);

	menu = menuBar()->addMenu("&Task");
	QAction* runAction = new QAction("Run");
	menu->addAction(runAction);

	connect(runAction, SIGNAL(triggered()), this, SLOT (handleRunButton()));
	connect(slider, SIGNAL (valueChanged(int)), this, SLOT (handleSliderValueChange()));
}

void BleFrame::handleRunButton()
{
	this->get_default_data();
	this->updateInputData();
	std::cout << "sc = " << get_shock_front(data->phys) << std::endl;
	this->make_grid();
	this->set_initial_cond();

	int index = 1;
	double sumT = 0.;
	while (sumT < data->model->period) {
		std::vector<double> s_prev = results[index-1]->s;

		std::vector<double> p = this->solve_press(s_prev);

		double t = ble_src::get_time_step(grd, s_prev, data);

		std::vector<double> s = this->solve_satur(t, s_prev);
		sumT += t;

		std::shared_ptr<ble_src::DynamicData> d (new ble_src::DynamicData());
		d->t = sumT;
		d->p = p;
		d->s = s;

		results.push_back(d);
	
		this->fill_time_series(index);
		index++;

	}

	int count = results.size();
	slider->setTickInterval(1.);
	slider->setMinimum(1);
	slider->setMaximum(count);
	slider->setValue(1);
}

BleFrame::~BleFrame()
{
}

void BleFrame::handleSliderValueChange()
{
	int value = slider->value() - 1;
	update_time_info(value);
	fill_time_series(value);
}

void BleFrame::update_time_info(int index)
{
	int count = results.size();
	std::ostringstream oss;
	oss << index + 1 << "/" << count;
	label->setText(QString::fromStdString(oss.str()));
}

void BleFrame::get_default_data()
{
	data = std::make_shared<ble_src::InputData>();
	data->phys->kmu = 0.125;
	data->phys->n_oil = 2;
	data->phys->n_wat = 2;
	data->phys->poro = 1.;
	data->phys->perm = 1.;

	data->model->period = 500.;

	data->grd->l = 10.;
	data->grd->n = 200;
	data->grd->type = ble_src::GridTypeEnum::kRegular;

	data->satSetts->cur_val = 0.9;
	data->satSetts->pN = 10;
	data->satSetts->type == ble_src::SaturSolverType::kExplicit;
}

void BleFrame::make_grid()
{
	grd = ble_src::make_grid(data);
}

void BleFrame::set_initial_cond()
{
	std::vector<double> s(grd->cells.size(), 0.);
	std::vector<double> p(grd->cells.size(), 1.);

	std::shared_ptr<ble_src::DynamicData> d (new ble_src::DynamicData());
	d->t = 0;
	d->p = p;
	d->s = s;

	results.push_back(d);
}

std::vector<double> BleFrame::solve_press(const std::vector<double>& s)
{
	std::vector<double> result = ble_src::solve_press(this->grd, s, data->phys);
	ble_src::calc_u(result, s, data->phys, grd);

	return result;
}

std::vector<double> BleFrame::solve_satur(const double tau, const std::vector<double>& s)
{
	return ble_src::solve_satur(tau, s, data, this->grd);
}

void BleFrame::fill_time_series(int index)
{
	std::shared_ptr<ble_src::DynamicData> d = results[index];

	std::ostringstream oss;
	oss.str("");
	oss << "t = " << d->t;

	chart->setTitle(QString::fromStdString(oss.str()));
	try{
		chart->removeSeries(series_press);
		chart->removeSeries(series_sat_num);
	}
	catch(...){
	}

	std::vector<double> p = results[index]->p;
	std::vector<double> s = results[index]->s;

	series_press = new QLineSeries();
	series_sat_num = new QLineSeries();
	for (auto &cl: grd->cells) {
		series_press->append(cl->cntr, p[cl->ind]);
		series_sat_num->append(cl->cntr, s[cl->ind]);
	}
	
	chart->addSeries(series_press);
	chart->setAxisX(axisX, series_press);
	chart->setAxisY(axisYPress, series_press);

	chart->addSeries(series_sat_num);
	chart->setAxisX(axisX, series_sat_num); // obsolete
	chart->setAxisY(axisYSat, series_sat_num); // obsolete
}

void BleFrame::updateInputData()
{
	data->model->period = dataWidget->ModelData->Period->value();
}

}

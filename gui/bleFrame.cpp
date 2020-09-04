#include "bleFrame.hpp"

#include <sstream>

#include <QCoreApplication>

#include "makeGrid.hpp"
#include "pressureSolver.hpp"

namespace ble_gui{

BleFrame::BleFrame(QWidget* parent)
	: QMainWindow(parent)
{
	central = new QWidget(this);
	layout = new QGridLayout;

	prev = new QPushButton("<-");
	layout->addWidget(prev, 1, 0);

	next = new QPushButton("->");
	layout->addWidget(next, 1, 2);

	timeStepInfo = new QLineEdit();
	timeStepInfo->setReadOnly(true);
	timeStepInfo->setAlignment(Qt::AlignCenter);
	layout->addWidget(timeStepInfo, 1, 1);

	run_button = new QPushButton("Run");
	layout->addWidget(run_button, 2, 0, 1, 3);

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

	chartView = new QChartView(chart);
	layout->addWidget(chartView, 0, 0, 1, 3);

	central->setLayout(layout);

	setCentralWidget(central);
	setWindowTitle("Ble Frame");
	this->setFixedSize(600, 400);

	connect(run_button, SIGNAL (released()), this, SLOT (handleRunButton()));
	connect(prev, SIGNAL (released()), this, SLOT (handlePrevButton()));
	connect(next, SIGNAL (released()), this, SLOT (handleNextButton()));
}

void BleFrame::handleRunButton()
{
	this->get_default_data();
	this->make_grid();
	this->set_initial_cond();

	int index = 1;
	double sumT = 0.;
	while (index < 10) {
		double t = 0.1;
		std::vector<double> s_prev = results[0]->s;
		std::vector<double> p = this->solve_press(s_prev);
		std::vector<double> s = this->solve_satur();
		sumT += t;

		std::shared_ptr<ble_src::DynamicData> d (new ble_src::DynamicData());
		d->t = sumT;
		d->p = p;
		d->s = s;

		results.push_back(d);
	
		this->fill_time_series(index);
		index++;

	}

	update_time_info(showIndex);
	fill_time_series(showIndex);
}

BleFrame::~BleFrame()
{
}

void BleFrame::handlePrevButton()
{
	if (showIndex < 1)
		return;
	showIndex--;

	update_time_info(showIndex);
	fill_time_series(showIndex);
}

void BleFrame::handleNextButton()
{
	int count = results.size();
	if (showIndex > count - 2)
		return;
	showIndex++;

	update_time_info(showIndex);
	fill_time_series(showIndex);
}

void BleFrame::update_time_info(int index)
{
	int count = results.size();
	std::ostringstream oss;
	oss << index + 1 << "/" << count;
	timeStepInfo->setText(QString::fromStdString(oss.str()));
}

void BleFrame::get_default_data()
{
	data = std::make_shared<ble_src::InputData>();
	data->phys->kmu = 0.125;
	data->phys->n_oil = 2;
	data->phys->n_wat = 2;
	data->phys->poro = 1.;
	data->phys->perm = 1.;

	data->model->period = 1.;

	data->grd->l = 10.;
	data->grd->n = 10;
	data->grd->type = ble_src::GridTypeEnum::kRegular;
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
	return ble_src::solve_press(this->grd, s);
}

std::vector<double> BleFrame::solve_satur()
{
	std::vector<double> result(grd->cells.size(), 0.);
	return result;
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
	}
	catch(...){
	}
	

	std::vector<double> p = results[index]->p;

	series_press = new QLineSeries();
	for (auto &cl: grd->cells) {
		series_press->append(cl->cntr, p[cl->ind]);
	}
	
	chart->addSeries(series_press);
	chart->setAxisX(axisX, series_press);
	chart->setAxisY(axisYPress, series_press);
}

}

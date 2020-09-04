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

	label = new QLabel("Test");
	layout->addWidget(label, 2, 1);

	run_button = new QPushButton("Run");
	layout->addWidget(run_button, 2, 0);

	chart = new QChart();
	chart->legend()->hide();
	chart->createDefaultAxes();
	chart->setTitle("p/s");

	chartView = new QChartView(chart);
	layout->addWidget(chartView, 0, 0, 1, 2);

	central->setLayout(layout);

	setCentralWidget(central);
	setWindowTitle("Ble Frame");
	this->setFixedSize(600, 400);

	connect(run_button, SIGNAL (released()), this, SLOT (handleRunButton()));
}

void BleFrame::handleRunButton()
{
	this->get_default_data();
	this->make_grid();
	this->set_initial_cond();

	int index = 1;
	while (true) {
		double t = 0.1;
		std::vector<double> s_prev = results[0]->s;
		std::vector<double> p = this->solve_press(s_prev);
		std::vector<double> s = this->solve_satur();

		std::shared_ptr<ble_src::DynamicData> d (new ble_src::DynamicData());
		d->t = t;
		d->p = p;
		d->s = s;

		results.push_back(d);
	
		this->fill_time_series(index);
		index++;


		break;
	}

	//std::ostringstream oss;
	//oss << "cell count = " << grd->cells.size();
	//QString qstr = QString::fromStdString(oss.str());

	//label->setText(qstr);
}

BleFrame::~BleFrame()
{
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
	//try{
		//chart->removeSeries(series_press);
	//}
	//catch(...){
	//}
	
	std::ostringstream oss;

	std::vector<double> p = results[index]->p;
	//oss.str("");
	//oss << "p size = " << p.size();

	//label->setText(QString::fromStdString(oss.str()));

	series_press = new QLineSeries();
	for (auto &cl: grd->cells) {
		oss.str("");
		oss << "x = "<< cl->cntr << ", y = " << p[cl->ind];
		label->setText(QString::fromStdString(oss.str()));
		series_press->append(cl->cntr, p[cl->ind]);
	}
	
	chart->addSeries(series_press);
}

}

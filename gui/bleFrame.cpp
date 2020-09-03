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
	run_button = new QPushButton("Run");

	label = new QLabel("Test");
	layout->addWidget(label, 1, 0);

	layout->addWidget(run_button, 0, 0);
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
	this->solve_press();

	std::ostringstream oss;
	oss << "cell count = " << grd->cells.size();
	QString qstr = QString::fromStdString(oss.str());

	label->setText(qstr);
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

void BleFrame::solve_press()
{
	std::vector<double> s = results[results.size()-1]->s;
	std::vector<double> p = ble_src::solve_press(this->grd, s);
}

}

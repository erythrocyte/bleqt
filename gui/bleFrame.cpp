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

namespace ble_gui
{

	BleFrame::BleFrame(QWidget *parent)
		: QMainWindow(parent)
	{
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
		this->setFixedSize(1100, 700);

		QCommonStyle *style = new QCommonStyle();
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
		QAction *showSettings = dock->toggleViewAction();
		showSettings->setIcon(style->standardIcon(QStyle::SP_FileDialogDetailedView));
		menu->addAction(showSettings);

		menu = menuBar()->addMenu("&Task");
		QAction *runAction = new QAction("Run");
		menu->addAction(runAction);

		this->set_default_data();
		this->update_sc(true);

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

		connect(runAction, SIGNAL(triggered()), this, SLOT(handleRunButton()));
		connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChange()));
	}

	void BleFrame::handleRunButton()
	{
		auto start = std::chrono::high_resolution_clock::now();

		results.clear();
		slider->setValue(1);
		label->setText("");

		this->updateInputData();
		this->make_grid();
		this->set_initial_cond();

		statusLabel->setText(tr("calculation status: "));

		double sc = ble_src::get_shock_front(data->phys);

		int index = 1;
		int pressIndex = 0;
		double sumT = 0.;
		double sumU = 0.;
		while (sumT < data->model->period)
		{
			std::vector<double> s_prev = results[index - 1]->s;

			std::vector<double> p = results[index - 1]->p;
			if (pressIndex == 0 || pressIndex == data->satSetts->pN)
			{
				p = this->solve_press(s_prev);
				pressIndex = 0;
			}
			pressIndex++;

			double t = ble_src::get_time_step(grd, s_prev, data);

			sumU += ble_src::getULiqInject(grd) * t;
			std::vector<std::tuple<double, double>> xs_an = ble_src::get_satur_exact(sc, sumU, data);

			std::vector<double> s = this->solve_satur(t, s_prev);
			sumT += t;

			std::shared_ptr<ble_src::DynamicData> d(new ble_src::DynamicData());
			d->t = sumT;
			d->p = p;
			d->s = s;
			d->s_an = xs_an;

			results.push_back(d);

			this->fill_time_series(graphFirst, index);
			graphFirst = false;
			index++;

			double perc = std::min(100.0, (sumT / data->model->period * 100.0));
			statusProgressBar->setValue(perc);
		}

		int count = results.size();
		slider->setMaximum(count);
		handleSliderValueChange();

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;

		std::ostringstream oss;
		oss << "calculation completed in " << std::fixed << std::setprecision(1) << diff.count() << " s.";

		statusLabel->setText(QString::fromStdString(oss.str()));
	}

	BleFrame::~BleFrame()
	{
	}

	void BleFrame::handleSliderValueChange()
	{
		int value = slider->value() - 1;
		if (value < results.size())
		{
			update_time_info(value);
			fill_time_series(false, value);
		}
	}

	void BleFrame::update_time_info(int index)
	{
		int count = results.size();
		std::ostringstream oss;
		oss << index + 1 << "/" << count;
		label->setText(QString::fromStdString(oss.str()));
	}

	void BleFrame::set_default_data()
	{
		data = std::make_shared<ble_src::InputData>();
		data->phys->kmu = 0.125;
		data->phys->n_oil = 2;
		data->phys->n_wat = 2;
		data->phys->poro = 1.;
		data->phys->perm = 1.;

		data->model->period = 500.;

		data->grd->l = 10.;
		data->grd->n = 2000;
		data->grd->type = ble_src::GridTypeEnum::kRegular;

		data->satSetts->cur_val = 0.005;
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

		std::shared_ptr<ble_src::DynamicData> d(new ble_src::DynamicData());
		d->t = 0;
		d->p = p;
		d->s = s;

		results.push_back(d);
	}

	std::vector<double> BleFrame::solve_press(const std::vector<double> &s)
	{
		std::vector<double> result = ble_src::solve_press(this->grd, s, data->phys);
		ble_src::calc_u(result, s, data->phys, grd);

		return result;
	}

	std::vector<double> BleFrame::solve_satur(const double tau, const std::vector<double> &s)
	{
		return ble_src::solve_satur(tau, s, data, this->grd);
	}

	void BleFrame::fill_time_series(bool init, int index)
	{
		std::shared_ptr<ble_src::DynamicData> d = results[index];

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

		std::vector<double> p = results[index]->p;
		std::vector<double> s = results[index]->s;

		for (auto &cl : grd->cells)
		{
			series_press->append(cl->cntr, p[cl->ind]);
			series_sat_num->append(cl->cntr, s[cl->ind]);
		}

		std::vector<std::tuple<double, double>> xs_an = results[index]->s_an;
		for (auto &v : xs_an)
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

	void BleFrame::updateInputData()
	{
		data->model->period = dataWidget->ModelData->Period->value();

		data->phys->kmu = dataWidget->PhysData->Kmu->value();
		data->phys->n_oil = dataWidget->PhysData->Noil->value();
		data->phys->n_wat = dataWidget->PhysData->Nwat->value();
		data->phys->perm = dataWidget->PhysData->Perm->value();
		data->phys->poro = dataWidget->PhysData->Poro->value();

		data->satSetts->cur_val = dataWidget->SaturSolverSetts->Curant->value();
		data->satSetts->pN = dataWidget->SaturSolverSetts->RecalcPressN->value();


		data->grd->l = dataWidget->GridSetts->Length->value();
		data->grd->n = dataWidget->GridSetts->CellCount->value();

		this->update_sc(false);
	}

	void BleFrame::update_sc(bool init)
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

		double sc = ble_src::get_shock_front(data->phys);
		series_sc->append(0.0, sc);
		series_sc->append(data->grd->l, sc);
		chart->addSeries(series_sc);
		chart->setAxisX(axisX, series_sc);
		chart->setAxisY(axisYSat, series_sc);
	}

} // namespace ble_gui

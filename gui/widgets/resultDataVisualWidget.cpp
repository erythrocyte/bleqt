#include "resultDataVisualWidget.hpp"

#include <sstream>

#include "shockFront.hpp"

#include <QGridLayout>

ble_gui::widgets::ResultDataVisualWidget::ResultDataVisualWidget(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *layout = new QGridLayout();

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
	axisX->setLabelFormat("%g");
	axisX->setTickCount(1);

	axisYSat = new QValueAxis();
	axisYSat->setTitleText("s / p");
	axisYSat->setLabelFormat("%g");
	axisYSat->setTickCount(5);
	axisYSat->setMin(0.);
	axisYSat->setMax(1.);

	chartView = new QChartView(chart);
	layout->addWidget(chartView, 0, 0, 1, 11);

	series_press = new QLineSeries();
	series_press->setName("p");

	series_sat_num = new QLineSeries();
	series_sat_num->setName("s_num");

	series_sat_an = new QLineSeries();
	series_sat_an->setName("s_an");

	chart->addSeries(series_press);
	chart->addSeries(series_sat_num);
	chart->addSeries(series_sat_an);

	series_sc = new QLineSeries();
	QPen pen;
	pen.setStyle(Qt::DotLine);
	pen.setWidth(2);
	// pen.setBrush(Qt::green);
	series_sc->setPen(pen);
	series_sc->setName(tr("sc"));

	setLayout(layout);

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChange()));
}

void ble_gui::widgets::ResultDataVisualWidget::setData(const std::shared_ptr<ble_src::BleResultData> data,
													   std::function<void(double)> progress)
{
	_data = data;
	// clear all;
	slider->setValue(1);
	label->setText("");

	slider->setMaximum(_data->data.size());
}

void ble_gui::widgets::ResultDataVisualWidget::handleSliderValueChange()
{
	int value = slider->value() - 1;
	if (value < _data->data.size())
	{
		update_time_info(value);
		fill_time_series(false, _data->data[value]);
	}
}

void ble_gui::widgets::ResultDataVisualWidget::fill_time_series(bool init,
																const std::shared_ptr<ble_src::DynamicData> d)
{
	std::ostringstream oss;
	oss.str("");
	oss << "t = " << d->t;

	chart->setTitle(QString::fromStdString(oss.str()));

	chart->removeSeries(series_press);
	chart->removeSeries(series_sat_num);
	chart->removeSeries(series_sat_an);

	series_press->clear();
	series_sat_num->clear();
	series_sat_an->clear();

	for (auto &cl : _data->grd->cells)
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
	chart->addSeries(series_sat_num);
	chart->addSeries(series_sat_an);

	chart->setAxisX(axisX, series_press);
	chart->setAxisY(axisYSat, series_press);

	chart->setAxisX(axisX, series_sat_num);	   // obsolete
	chart->setAxisY(axisYSat, series_sat_num); // obsolete

	chart->setAxisX(axisX, series_sat_an);	  // obsolete
	chart->setAxisY(axisYSat, series_sat_an); // obsolete
}

void ble_gui::widgets::ResultDataVisualWidget::update_sc_series(double l, double sc)
{
	chart->removeSeries(series_sc);
	series_sc->clear();

	series_sc->append(0.0, sc);
	series_sc->append(l, sc);
	chart->addSeries(series_sc);
	chart->setAxisX(axisX, series_sc);
	chart->setAxisY(axisYSat, series_sc);
}

void ble_gui::widgets::ResultDataVisualWidget::set_sc_visible(bool visible)
{
	series_sc->setVisible(visible);
}

void ble_gui::widgets::ResultDataVisualWidget::update_time_info(int index)
{
	int count = _data->data.size();
	std::ostringstream oss;
	oss << index + 1 << "/" << count;
	label->setText(QString::fromStdString(oss.str()));
}

#include "fluidParamsVisualWidget.hpp"

#include "workRp.hpp"
#include "shockFront.hpp"
#include "commonMath.hpp"

#include <QGridLayout>

ble_gui::widgets::FluidParamsVisualWidget::FluidParamsVisualWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout();

    _chart = new QChart();
    _chart->legend()->setVisible(true);

    // Настройка осей графика
    _axisS = new QValueAxis();
    _axisS->setTitleText("s");
    _axisS->setLabelFormat("%g");
    _axisS->setTickCount(5);
    _axisS->setRange(0., 1.);

    _axis_kY = new QValueAxis();
    _axis_kY->setTitleText("k, fbl");
    _axis_kY->setLabelFormat("%g");
    _axis_kY->setTickCount(5);
    _axis_kY->setRange(0., 1.);

    _axis_dfY = new QValueAxis();
    _axis_dfY->setTitleText("dfdbl");
    _axis_dfY->setLabelFormat("%g");
    _axis_dfY->setTickCount(5);
    _axis_dfY->setMin(0.);

    _chartView = new QChartView(_chart);
    layout->addWidget(_chartView, 0, 0, 1, 11);

    QPen pen;
    pen.setWidth(2);

    _series_kw = new QLineSeries();
    _series_kw->setName("kw");
    pen.setBrush(Qt::GlobalColor::blue);
    _series_kw->setPen(pen);

    _series_koil = new QLineSeries();
    _series_koil->setName("koil");
    pen.setBrush(Qt::GlobalColor::red);
    _series_koil->setPen(pen);

    _series_fbl = new QLineSeries();
    _series_fbl->setName("fbl");
    pen.setBrush(Qt::GlobalColor::green);
    _series_fbl->setPen(pen);

    _series_dfbl = new QLineSeries();
    _series_dfbl->setName("dfbl");
    pen.setBrush(Qt::GlobalColor::magenta);
    _series_dfbl->setPen(pen);

    _series_sc = new QLineSeries();
    _series_sc->setName("sc");
    pen.setBrush(Qt::GlobalColor::darkCyan);
    pen.setStyle(Qt::DashDotDotLine);
    _series_sc->setPen(pen);

    _chart->addSeries(_series_kw);
    _chart->addSeries(_series_koil);
    _chart->addSeries(_series_fbl);
    _chart->addSeries(_series_dfbl);
    _chart->addSeries(_series_sc);

    _chart->addAxis(_axisS, Qt::AlignBottom);
    _chart->addAxis(_axis_kY, Qt::AlignLeft);
    _chart->addAxis(_axis_dfY, Qt::AlignRight);

    // _series_kw->attachAxis(_axisS); // use instead of setAxisX, 
    // _series_kw->attachAxis(_axis_kY); // but does not work for different points;

    // _series_koil->attachAxis(_axisS);
    // _series_koil->attachAxis(_axis_kY);

    // _series_fbl->attachAxis(_axisS);
    // _series_fbl->attachAxis(_axis_kY);

    // _series_dfbl->attachAxis(_axisS);
    // _series_dfbl->attachAxis(_axis_dfY);

    // _series_sc->attachAxis(_axisS);
    // _series_sc->attachAxis(_axis_dfY);

    setLayout(layout);
}

void ble_gui::widgets::FluidParamsVisualWidget::update_view(const std::shared_ptr<ble_src::PhysData> data,
                                                            double sc)
{
    _chart->removeSeries(_series_kw);
    _chart->removeSeries(_series_koil);
    _chart->removeSeries(_series_fbl);
    _chart->removeSeries(_series_dfbl);
    _chart->removeSeries(_series_sc);

    _series_kw->clear();
    _series_koil->clear();
    _series_fbl->clear();
    _series_dfbl->clear();
    _series_sc->clear();

    fill_data(data, sc);

    _chart->addSeries(_series_kw);
    _chart->addSeries(_series_koil);
    _chart->addSeries(_series_fbl);
    _chart->addSeries(_series_dfbl);
    _chart->addSeries(_series_sc);

    _chart->setAxisX(_axisS, _series_kw);
    _chart->setAxisY(_axis_kY, _series_kw);

    _chart->setAxisX(_axisS, _series_koil);   // TODO : obsolete
    _chart->setAxisY(_axis_kY, _series_koil); // obsolete

    _chart->setAxisX(_axisS, _series_fbl);   // obsolete
    _chart->setAxisY(_axis_kY, _series_fbl); // obsolete

    _chart->setAxisX(_axisS, _series_dfbl);    // obsolete
    _chart->setAxisY(_axis_dfY, _series_dfbl); // obsolete

    _chart->setAxisX(_axisS, _series_sc);    // obsolete
    _chart->setAxisY(_axis_kY, _series_sc); // obsolete
}

void ble_gui::widgets::FluidParamsVisualWidget::fill_data(const std::shared_ptr<ble_src::PhysData> data,
                                                          double sc)
{
    int n = 200;
    double ds = 1.0 / (n - 1);

    double max_dfbl = 1.0;

    double dsc = ble_src::get_fbl(sc, data);

    for (int k = 0; k < n; k++)
    {
        double s = ds * k;
        double kw = ble_src::get_kw(s, data);
        double koil = ble_src::get_koil(s, data);
        double fbl = ble_src::get_fbl(s, data);
        double dfbl = ble_src::get_dfbl(s, data);

        if (dfbl > max_dfbl)
            max_dfbl = dfbl;

        _series_kw->append(s, kw);
        _series_koil->append(s, koil);
        _series_fbl->append(s, fbl);
        _series_dfbl->append(s, dfbl);
    }

    double x_up = ble_src::common_math::get_value_lin_approx(0, 0, dsc, sc, 1.0);
    _series_sc->append(0., 0.);
    _series_sc->append(sc, dsc);
    _series_sc->append(x_up, 1.);
    _series_sc->append(sc, dsc);
    _series_sc->append(sc, 0.);

    _axis_dfY->setMax(max_dfbl);
}

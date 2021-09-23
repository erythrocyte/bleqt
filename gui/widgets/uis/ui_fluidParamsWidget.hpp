#ifndef BLE_GUI_WIDGETS_UI_FLUIDPARAMSVISUAL_H_
#define BLE_GUI_WIDGETS_UI_FLUIDPARAMSVISUAL_H_

#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QLineSeries>
#include <QValueAxis>
#include <QWidget>

using namespace QtCharts;

namespace ble::gui::widgets::UI {

class FluidParams {
public:
    QLineSeries* series_kw;
    QLineSeries* series_koil;
    QLineSeries* series_fbl;
    QLineSeries* series_dfbl;
    QLineSeries* series_sc;
    QGridLayout* layout;

    QValueAxis* axis_dfY;

    void retranslateUi(QWidget* widget)
    {
        _axisS->setTitleText("s");
        _axis_kY->setTitleText("k, f");
        axis_dfY->setTitleText("f'");
    }

    void setupUI(QWidget* widget)
    {
        layout = new QGridLayout(widget);

        chart = new QChart();
        chart->legend()->setVisible(true);

        // Настройка осей графика
        _axisS = new QValueAxis();
        _axisS->setLabelFormat("%g");
        _axisS->setTickCount(5);
        _axisS->setRange(0., 1.);

        _axis_kY = new QValueAxis();
        _axis_kY->setLabelFormat("%g");
        _axis_kY->setTickCount(5);
        _axis_kY->setRange(0., 1.);

        axis_dfY = new QValueAxis();
        axis_dfY->setLabelFormat("%.2f");
        axis_dfY->setTickCount(5);
        axis_dfY->setMin(0.);

        _chartView = new QChartView(chart);
        layout->addWidget(_chartView, 0, 0, 1, 11);

        QPen pen;
        pen.setWidth(2);

        series_kw = new QLineSeries();
        series_kw->setName("kw");
        pen.setBrush(Qt::GlobalColor::blue);
        series_kw->setPen(pen);

        series_koil = new QLineSeries();
        series_koil->setName("ko");
        pen.setBrush(Qt::GlobalColor::red);
        series_koil->setPen(pen);

        series_fbl = new QLineSeries();
        series_fbl->setName("f");
        pen.setBrush(Qt::GlobalColor::green);
        series_fbl->setPen(pen);

        series_dfbl = new QLineSeries();
        series_dfbl->setName("f'");
        pen.setBrush(Qt::GlobalColor::magenta);
        series_dfbl->setPen(pen);

        series_sc = new QLineSeries();
        series_sc->setName("sc");
        pen.setBrush(Qt::GlobalColor::darkCyan);
        pen.setStyle(Qt::DashDotDotLine);
        series_sc->setPen(pen);

        chart->addSeries(series_kw);
        chart->addSeries(series_koil);
        chart->addSeries(series_fbl);
        chart->addSeries(series_dfbl);
        chart->addSeries(series_sc);

        chart->addAxis(_axisS, Qt::AlignBottom);
        chart->addAxis(_axis_kY, Qt::AlignLeft);
        chart->addAxis(axis_dfY, Qt::AlignRight);

        series_kw->attachAxis(_axisS); // use instead of setAxisX,
        series_kw->attachAxis(_axis_kY); // but does not work for different points;

        series_koil->attachAxis(_axisS);
        series_koil->attachAxis(_axis_kY);

        series_fbl->attachAxis(_axisS);
        series_fbl->attachAxis(_axis_kY);

        series_sc->attachAxis(_axisS);
        series_sc->attachAxis(_axis_kY);

        series_dfbl->attachAxis(_axisS);
        series_dfbl->attachAxis(axis_dfY);

        retranslateUi(widget);
    }

private:
    QChartView* _chartView;
    QChart* chart;

    QValueAxis* _axisS;
    QValueAxis* _axis_kY;
};

}

#endif
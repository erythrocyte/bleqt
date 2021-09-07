#ifndef BLEGUI_WIDGETS_UI_WELLWORLDATAWIDGET_H_
#define BLEGUI_WIDGETS_UI_WELLWORLDATAWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QLabel>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

namespace ble_gui::widgets {
namespace UI {
    class WellWorkData {
    public:
        QChart* Chart;
        QLineSeries* SeriesQliq;
        QLineSeries* SeriesQoil;
        QLineSeries* SeriesQwat;
        QLineSeries* SeriesFw;

        void setupUi(QWidget* widget)
        {
            _layout = new QGridLayout(widget);

            Chart = new QChart();
            Chart->legend()->setVisible(true);

            // Настройка осей графика
            _axisX = new QValueAxis();
            _axisX->setLabelFormat("%g");
            _axisX->setTickCount(5);
            // _axisX->setRange(0., 1.);

            _axisQ = new QValueAxis();
            _axisQ->setLabelFormat("%g");
            _axisQ->setTickCount(5);            
            // _axisYSat->setRange(0., 1.);

            _axisFw = new QValueAxis();
            _axisFw->setLabelFormat("%g");
            _axisFw->setTickCount(5);
            _axisFw->setRange(0.0, 100.0);

            _chartView = new QChartView(Chart);
            _layout->addWidget(_chartView, 0, 0, 1, 11);

            SeriesQliq = new QLineSeries();
            SeriesQoil = new QLineSeries();
            SeriesQwat = new QLineSeries();
            SeriesFw = new QLineSeries();

            Chart->addAxis(_axisX, Qt::AlignBottom);
            Chart->addAxis(_axisQ, Qt::AlignLeft);
            Chart->addAxis(_axisFw, Qt::AlignRight);

            retranslateUi();
        }

        void retranslateUi()
        {
            _axisX->setTitleText("t");
            _axisQ->setTitleText("q");
            _axisFw->setTitleText("fw, %");
            SeriesQliq->setName("qliq");
            SeriesQoil->setName("qoil");
            SeriesQwat->setName("qwat");
            SeriesFw->setName("fw");
        }

        void setup_xaxis_max(double value)
        {
            _axisX->setRange(0.0, value);
        }

        void add_series()
        {
            Chart->addSeries(SeriesQliq);
            Chart->addSeries(SeriesQoil);
            Chart->addSeries(SeriesQwat);
            Chart->addSeries(SeriesFw);

            SeriesQliq->attachAxis(_axisX);
            SeriesQliq->attachAxis(_axisQ);
            SeriesQoil->attachAxis(_axisX);
            SeriesQoil->attachAxis(_axisQ);
            SeriesQwat->attachAxis(_axisX);
            SeriesQwat->attachAxis(_axisQ);
            SeriesFw->attachAxis(_axisX);
            SeriesFw->attachAxis(_axisFw);

            _axisQ->setMin(0.0);
        }

    private:
        QGridLayout* _layout;
        QChartView* _chartView;
        QValueAxis* _axisX;
        QValueAxis* _axisQ;
        QValueAxis* _axisFw;
    };
}

}

#endif

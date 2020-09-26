#ifndef BLEGUI_WIDGETS_UI_FLUIDPARAMSVISUAL_H_
#define BLEGUI_WIDGETS_UI_FLUIDPARAMSVISUAL_H_

#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QWidget>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

namespace ble_gui {
namespace widgets {

    namespace UI {

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
                _axis_kY->setTitleText("k, fbl");
                axis_dfY->setTitleText("dfdbl");
            }

            void setupUI(QWidget* widget)
            {
                layout = new QGridLayout();

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
                series_koil->setName("koil");
                pen.setBrush(Qt::GlobalColor::red);
                series_koil->setPen(pen);

                series_fbl = new QLineSeries();
                series_fbl->setName("fbl");
                pen.setBrush(Qt::GlobalColor::green);
                series_fbl->setPen(pen);

                series_dfbl = new QLineSeries();
                series_dfbl->setName("dfbl");
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

                chart->setAxisX(_axisS, series_kw);
                chart->setAxisY(_axis_kY, series_kw);

                chart->setAxisX(_axisS, series_koil); // TODO : obsolete
                chart->setAxisY(_axis_kY, series_koil); // obsolete

                chart->setAxisX(_axisS, series_fbl); // obsolete
                chart->setAxisY(_axis_kY, series_fbl); // obsolete

                chart->setAxisX(_axisS, series_dfbl); // obsolete
                chart->setAxisY(axis_dfY, series_dfbl); // obsolete

                chart->setAxisX(_axisS, series_sc); // obsolete
                chart->setAxisY(_axis_kY, series_sc); // obsolete

                retranslateUi(widget);
            }

        private:
            QChartView* _chartView;
            QChart* chart;

            QValueAxis* _axisS;
            QValueAxis* _axis_kY;
        };

    }
}
}

#endif
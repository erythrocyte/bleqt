#ifndef BLE_GUI_WIDGETS_UI_DATAVISUAL_H_
#define BLE_GUI_WIDGETS_UI_DATAVISUAL_H_

#include <functional>
#include <iostream>
#include <memory>

#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QLabel>
#include <QLineSeries>
#include <QSlider>
#include <QValueAxis>

using namespace QtCharts;

namespace ble::gui::widgets::UI {
class ResultData {
public:
    QChart* Chart;
    QLineSeries* SeriesPress;
    QLineSeries* SeriesPressAn;
    QLineSeries* SeriesSatNum;
    QLineSeries* SeriesSatAn;
    QLineSeries* SeriesSc;
    QSlider* Slider;
    QLabel* Label;

    void setupUi(QWidget* widget)
    {
        _layout = new QGridLayout(widget);

        Slider = new QSlider(Qt::Orientation::Horizontal);
        _layout->addWidget(Slider, 1, 0, 1, 10);
        Slider->setTickInterval(1.);
        Slider->setMinimum(1);
        Slider->setMaximum(1);
        Slider->setValue(1);

        Label = new QLabel();
        _layout->addWidget(Label, 1, 10);

        Chart = new QChart();
        Chart->legend()->setVisible(true);

        // Настройка осей графика
        _axisX = new QValueAxis();
        _axisX->setLabelFormat("%g");
        _axisX->setTickCount(5);
        _axisX->setRange(0., 1.);

        _axisYSat = new QValueAxis();
        _axisYSat->setLabelFormat("%g");
        _axisYSat->setTickCount(5);
        _axisYSat->setRange(0., 1.);

        _axisYPress = new QValueAxis();
        _axisYPress->setLabelFormat("%g");
        _axisYPress->setTickCount(5);
        _axisYPress->setRange(0., 1.);

        _chartView = new QChartView(Chart);
        _layout->addWidget(_chartView, 0, 0, 1, 11);

        SeriesPress = new QLineSeries();
        SeriesPressAn = new QLineSeries();
        SeriesSatNum = new QLineSeries();
        SeriesSatAn = new QLineSeries();

        Chart->addSeries(SeriesPress);
        Chart->addSeries(SeriesPressAn);
        Chart->addSeries(SeriesSatNum);
        Chart->addSeries(SeriesSatAn);

        Chart->addAxis(_axisX, Qt::AlignBottom);
        Chart->addAxis(_axisYPress, Qt::AlignLeft);
        Chart->addAxis(_axisYSat, Qt::AlignRight);

        SeriesSc = new QLineSeries();
        _pen.setStyle(Qt::DotLine);
        _pen.setWidth(2);
        // pen.setBrush(Qt::green);
        SeriesSc->setPen(_pen);
        Chart->addSeries(SeriesSc);

        retranslateUi();
    }

    void retranslateUi()
    {
        _axisX->setTitleText("x");
        _axisYSat->setTitleText("s");
        _axisYPress->setTitleText("p");
        SeriesPress->setName("p");
        SeriesPressAn->setName("p_an");
        SeriesSatNum->setName("s_num");
        SeriesSatAn->setName("s_an");
        SeriesSc->setName("sc");
    }

private:
    QGridLayout* _layout;
    QPen _pen;
    QChartView* _chartView;
    QValueAxis* _axisX;
    QValueAxis* _axisYPress;
    QValueAxis* _axisYSat;
};

}

#endif

#ifndef BLEGUI_WIDGETS_DATAVISUALWIDGET_H_
#define BLEGUI_WIDGETS_DATAVISUALWIDGET_H_

#include <iostream>
#include <memory>
#include <functional>

#include "bleResultData.hpp"

#include <QLabel>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QSlider>

using namespace QtCharts;

namespace ble_gui
{
    namespace widgets
    {
        class ResultDataVisualWidget : public QWidget
        {
            Q_OBJECT

        private:
            QChartView *chartView;
            QChart *chart;
            QLineSeries *series_press;
            QLineSeries *series_sat_num;
            QLineSeries *series_sat_an;
            QLineSeries *series_sc;
            QValueAxis *axisX;
            QValueAxis *axisYPress;
            QValueAxis *axisYSat;
            QSlider *slider;
            QLabel *label;

            bool _firstInit = true;

            std::shared_ptr<ble_src::BleResultData> _data;

            void update_time_info(int index);
            void fill_time_series(bool init, const std::shared_ptr<ble_src::DynamicData> d);

        public:
            ResultDataVisualWidget(QWidget *parent = nullptr);
            ~ResultDataVisualWidget() {}

            void setData(const std::shared_ptr<ble_src::BleResultData> data,
                         std::function<void(double)> progress);
            void update_sc_series(double l, double sc);
            void set_sc_visible(bool visible);

        private slots:
            void handleSliderValueChange();
        };
    } // namespace widgets
} // namespace ble_gui

#endif
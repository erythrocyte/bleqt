#ifndef BLEGUI_WIDGETS_FLUIDPARAMSVISUALWIDGET_H_
#define BLEGUI_WIDGETS_FLUIDPARAMSVISUALWIDGET_H_

#include <iostream>
#include <memory>
#include <functional>

#include "physData.hpp"

#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

namespace ble_gui
{
    namespace widgets
    {
        class FluidParamsVisualWidget : public QWidget
        {
            Q_OBJECT

        private:
            QChartView *_chartView;
            QChart *_chart;
            QLineSeries *_series_kw;
            QLineSeries *_series_koil;
            QLineSeries *_series_fbl;
            QLineSeries *_series_dfbl;
            QLineSeries *_series_sc;
            QValueAxis *_axisS;
            QValueAxis *_axis_kY;
            QValueAxis *_axis_dfY;

            void fill_data(const std::shared_ptr<ble_src::PhysData> data, double sc);

        public:
            FluidParamsVisualWidget(QWidget *parent = nullptr);
            ~FluidParamsVisualWidget() {}

            void update_view(const std::shared_ptr<ble_src::PhysData> data, double sc);
        };
    } // namespace widgets
} // namespace ble_gui

#endif
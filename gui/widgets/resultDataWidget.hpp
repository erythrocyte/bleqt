#ifndef BLEGUI_WIDGETS_DATAVISUALWIDGET_H_
#define BLEGUI_WIDGETS_DATAVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "bleResultData.hpp"

#include <QChart>
#include <QChartView>
#include <QLabel>
#include <QLineSeries>
#include <QSlider>
#include <QValueAxis>

using namespace QtCharts;

namespace ble_gui {
namespace widgets {
    class ResultDataVisualWidget : public QWidget {
        Q_OBJECT

    public:
        ResultDataVisualWidget(QWidget* parent = nullptr);
        ~ResultDataVisualWidget() { }

        void setData(const std::shared_ptr<ble_src::BleResultData> data,
            std::function<void(double)> progress);
        void update_sc_series(double l, double sc);
        void set_sc_visible(bool visible);

    private:
        QChartView* chartView;
        QChart* chart;
        QLineSeries* series_press;
        QLineSeries* series_sat_num;
        QLineSeries* series_sat_an;
        QLineSeries* series_sc;
        QValueAxis* axisX;
        QValueAxis* axisYPress;
        QValueAxis* axisYSat;
        QSlider* slider;
        QLabel* label;

        bool _firstInit = true;

        std::shared_ptr<ble_src::BleResultData> _data;

        void update_time_info(int index);
        void fill_time_series(bool init, const std::shared_ptr<ble_src::DynamicData> d);

    private slots:
        void handleSliderValueChange();
    };
} // namespace widgets
} // namespace ble_gui

#endif
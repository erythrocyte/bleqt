#ifndef BLEGUI_WIDGETS_FLUIDPARAMSVISUALWIDGET_H_
#define BLEGUI_WIDGETS_FLUIDPARAMSVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "physData.hpp"

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>

#include "uis/ui_fluidParamsVisualWidget.hpp"

using namespace QtCharts;

namespace ble_gui {
namespace widgets {

    class FluidParamsVisualWidget : public QWidget, public UI::FluidParamsVisual {
        Q_OBJECT

    public:
        FluidParamsVisualWidget(QWidget* parent = nullptr);
        ~FluidParamsVisualWidget() { delete ui; }

        void update_view(const std::shared_ptr<ble_src::PhysData> data, double sc);

    private:
        UI::FluidParamsVisual* ui;

        void fill_data(const std::shared_ptr<ble_src::PhysData> data, double sc);
    };
} // namespace widgets
} // namespace ble_gui

#endif
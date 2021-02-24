#ifndef BLEGUI_WIDGETS_DATAVISUALWIDGET_H_
#define BLEGUI_WIDGETS_DATAVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "bleResultData.hpp"

#include "uis/ui_resultDataWidget.hpp"

using namespace QtCharts;

namespace ble_gui::widgets {
class ResultDataWidget : public QWidget, private UI::ResultData {
    Q_OBJECT

public:
    ResultDataWidget(QWidget* parent = nullptr);
    ~ResultDataWidget() { delete ui; }

    void setData(const std::shared_ptr<ble_src::BleResultData> data,
        std::function<void(double)> progress);
    void update_sc_series(double l, double sc);
    void set_sc_visible(bool visible) { ui->SeriesSc->setVisible(visible); }

private:
    UI::ResultData* ui;

    bool _firstInit = true;

    std::shared_ptr<ble_src::BleResultData> _data;

    void update_time_info(int index);
    void fill_time_series(bool init, const std::shared_ptr<ble_src::DynamicData> d);

private slots:
    void handleSliderValueChange();
};

} // namespace ble_gui::widgets

#endif
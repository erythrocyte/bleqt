#ifndef BLE_GUI_WIDGETS_DATAVISUALWIDGET_H_
#define BLE_GUI_WIDGETS_DATAVISUALWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include "calc/models/bleResultData.hpp"
#include "common/models/boundCondType.hpp"

#include "uis/ui_resultDataWidget.hpp"

using namespace QtCharts;

namespace ble::gui::widgets {
class ResultDataWidget : public QWidget, private UI::ResultData {
    Q_OBJECT

public:
    ResultDataWidget(QWidget* parent = nullptr);
    ~ResultDataWidget() { delete ui; }

    void setData(const std::shared_ptr<ble::src::calc::models::BleResultData> data,
        src::common::models::BoundCondType::TypeEnum bound_type,
        std::function<void(double)> progress);
    void update_sc_series(double l, double sc);
    void set_sc_visible(bool visible) { ui->SeriesSc->setVisible(visible); }

private:
    UI::ResultData* ui;    

    bool _firstInit = true;
    bool m_playing = false;
    double m_interval = 1000;

    src::common::models::BoundCondType::TypeEnum m_bound_type;

    std::shared_ptr<ble::src::calc::models::BleResultData> _data;

    void subscribe();
    void update_time_info(int index);
    void fill_time_series(bool init, const std::shared_ptr<ble::src::common::models::DynamicData> d);
    void set_slider_value(int value);
    void stop_timer();

private slots:
    void handleSliderValueChange();
    void handleBtnSeekBackClick();
    void handleBtnStepBackClick();
    void handleBtnPlayPauseClick();
    void handleBtnStopClick();
    void handleBtnStepForwardClick();
    void handleBtnSeekForwardClick();
    void PlayDynamicData();
    void speedChanged();
};

} // namespace ble_gui::widgets

#endif
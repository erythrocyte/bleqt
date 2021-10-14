#include "resultDataWidget.hpp"

#include <sstream>

namespace ble::gui::widgets {

ResultDataWidget::ResultDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ResultData)
{
    ui->setupUi(this);
    ui->tool_bar_enabled(false);

    m_interval = ui->get_current_speed();
    subscribe();
}

void ResultDataWidget::subscribe()
{
    auto success = connect(ui->Slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChange()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BtnSeekBack, SIGNAL(triggered()), this, SLOT(handleBtnSeekBackClick()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BtnStepBack, SIGNAL(triggered()), this, SLOT(handleBtnStepBackClick()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BtnPlayPause, SIGNAL(triggered()), this, SLOT(handleBtnPlayPauseClick()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BtnStop, SIGNAL(triggered()), this, SLOT(handleBtnStopClick()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BtnStepForward, SIGNAL(triggered()), this, SLOT(handleBtnStepForwardClick()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BtnSeekForward, SIGNAL(triggered()), this, SLOT(handleBtnSeekForwardClick()));
    Q_ASSERT(success);

    success = connect(ui->Timer, &QTimer::timeout, this, &ResultDataWidget::PlayDynamicData);
    Q_ASSERT(success);
    ui->Timer->start(m_interval);

    success = connect(ui->SpeedLowQuarter, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);
    success = connect(ui->SpeedLowHalf, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);
    success = connect(ui->SpeedLowHalfQuarter, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);
    success = connect(ui->SpeedNormal, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);
    success = connect(ui->SpeedHighQuarter, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);
    success = connect(ui->SpeedHighHalf, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);
    success = connect(ui->SpeedHighTwice, &QAction::triggered, this, &ResultDataWidget::speedChanged);
    Q_ASSERT(success);

    success = connect(ui->PressGlobalLimit, &QCheckBox::stateChanged, this, &ResultDataWidget::pressLimitsChanged);
    Q_ASSERT(success);
}

void ResultDataWidget::setData(
    const std::shared_ptr<ble::src::calc::models::BleResultData> data,
    src::common::models::BoundCondType::TypeEnum bound_type,
    std::function<void(double)> progress)
{
    _data = data;
    m_bound_type = bound_type;
    ui->tool_bar_enabled(true);

    pressLimitsChanged();

    // clear all;
    set_slider_value(1);
    ui->Label->setText("");

    ui->Slider->setMaximum(_data->data.size());
    handleSliderValueChange(); // call slider value change handler. setValue does not call it;
}

void ResultDataWidget::handleSliderValueChange()
{
    int value = ui->Slider->value() - 1;
    if (value < static_cast<int>(_data->data.size())) {
        update_time_info(value);
        fill_time_series(false, _data->data[value]);
    }
}

void ResultDataWidget::fill_time_series(bool init,
    const std::shared_ptr<ble::src::common::models::DynamicData> d)
{
    std::ostringstream oss;
    oss.str("");
    oss << "t = " << d->t;

    ui->Chart->setTitle(QString::fromStdString(oss.str()));

    ui->SeriesPress->clear();
    ui->SeriesSatNum->clear();
    ui->SeriesSatAn->clear();
    ui->SeriesPressAn->clear();

    for (auto& cl : _data->grd->cells) {
        ui->SeriesPress->append(cl->cntr, d->p[cl->ind]);
        ui->SeriesSatNum->append(cl->cntr, d->s[cl->ind]);
        if (m_bound_type == src::common::models::BoundCondType::kConst) {
            ui->SeriesPressAn->append(cl->cntr, d->p_ex[cl->ind]);
        }
    }

    if (m_bound_type == src::common::models::BoundCondType::kConst) {
        for (auto& v : d->s_an) {
            double x1, s1;
            std::tie(x1, s1) = v;
            ui->SeriesSatAn->append(x1, s1);
        }
    }

    if (!m_press_global_lim)
        ui->set_press_axis_range(0.0, d->p[_data->grd->cells.size() - 1]);
}

void ResultDataWidget::update_sc_series(double l, double sc)
{
    ui->SeriesSc->clear();

    ui->SeriesSc->append(0.0, sc);
    ui->SeriesSc->append(l, sc);
}

void ResultDataWidget::update_time_info(int index)
{
    int count = _data->data.size();
    std::ostringstream oss;
    oss << index + 1 << "/" << count;
    ui->Label->setText(QString::fromStdString(oss.str()));
}

void ResultDataWidget::handleBtnSeekBackClick()
{
    stop_timer();
    set_slider_value(1);
}

void ResultDataWidget::handleBtnStepBackClick()
{
    stop_timer();
    set_slider_value(ui->Slider->value() - 1);
}

void ResultDataWidget::handleBtnPlayPauseClick()
{
    m_playing = !m_playing;
    ui->set_play_icon(m_playing);
}

void ResultDataWidget::handleBtnStopClick()
{
    stop_timer();
    set_slider_value(1);
}

void ResultDataWidget::handleBtnStepForwardClick()
{
    stop_timer();
    set_slider_value(ui->Slider->value() + 1);
}

void ResultDataWidget::handleBtnSeekForwardClick()
{
    stop_timer();
    set_slider_value(ui->Slider->maximum());
}

void ResultDataWidget::set_slider_value(int value)
{
    if (value > ui->Slider->maximum()) {
        m_playing = false;
        return;
    }

    ui->Slider->setValue(value);
}

void ResultDataWidget::PlayDynamicData()
{
    if (m_playing) {
        int value = ui->Slider->value();
        if (value == ui->Slider->maximum())
            value = 1;
        set_slider_value(value + 1);
    }
}

void ResultDataWidget::speedChanged()
{
    m_interval = ui->update_selected_speed(sender());
    ui->Timer->start(m_interval);
}

void ResultDataWidget::stop_timer()
{
    m_playing = false;
    ui->set_play_icon(m_playing);
}

void ResultDataWidget::pressLimitsChanged()
{
    m_press_global_lim = ui->PressGlobalLimit->isChecked();
    update_press_axis();
}

void ResultDataWidget::update_press_axis()
{
    if (_data == nullptr)
        return;

    if (m_press_global_lim)
        ui->set_press_axis_range(0.0, get_press_max());

    handleSliderValueChange();
}

double ResultDataWidget::get_press_max()
{
    double result = 0.0;
    size_t cind = _data->grd->cells.size() - 1;
    if (_data == nullptr)
        return 1.0;

    for (auto& d : _data->data)
        if (d->p[cind] > result)
            result = d->p[cind];

    return result;
}

}

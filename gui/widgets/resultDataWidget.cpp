#include "resultDataWidget.hpp"

#include <sstream>

#include "shockFront.hpp"

ble_gui::widgets::ResultDataVisualWidget::ResultDataVisualWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ResultDataVisual)
{
    ui->setupUi(this);

    connect(ui->Slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChange()));
}

void ble_gui::widgets::ResultDataVisualWidget::setData(
    const std::shared_ptr<ble_src::BleResultData> data,
    std::function<void(double)> progress)
{
    _data = data;
    // clear all;
    ui->Slider->setValue(1);
    ui->Label->setText("");

    ui->Slider->setMaximum(_data->data.size());
    handleSliderValueChange(); // call slider value change handler. setValue does not call it;
}

void ble_gui::widgets::ResultDataVisualWidget::handleSliderValueChange()
{
    int value = ui->Slider->value() - 1;
    if (value < _data->data.size()) {
        update_time_info(value);
        fill_time_series(false, _data->data[value]);
    }
}

void ble_gui::widgets::ResultDataVisualWidget::fill_time_series(bool init,
    const std::shared_ptr<ble_src::DynamicData> d)
{
    std::ostringstream oss;
    oss.str("");
    oss << "t = " << d->t;

    ui->Chart->setTitle(QString::fromStdString(oss.str()));

    ui->SeriesPress->clear();
    ui->SeriesSatNum->clear();
    ui->SeriesSatAn->clear();

    for (auto& cl : _data->grd->cells) {
        ui->SeriesPress->append(cl->cntr, d->p[cl->ind]);
        ui->SeriesSatNum->append(cl->cntr, d->s[cl->ind]);
    }

    for (auto& v : d->s_an) {
        double x1, s1;
        std::tie(x1, s1) = v;
        ui->SeriesSatAn->append(x1, s1);
    }
}

void ble_gui::widgets::ResultDataVisualWidget::update_sc_series(double l, double sc)
{
    ui->SeriesSc->clear();

    ui->SeriesSc->append(0.0, sc);
    ui->SeriesSc->append(l, sc);
}

void ble_gui::widgets::ResultDataVisualWidget::update_time_info(int index)
{
    int count = _data->data.size();
    std::ostringstream oss;
    oss << index + 1 << "/" << count;
    ui->Label->setText(QString::fromStdString(oss.str()));
}
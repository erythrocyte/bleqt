#include "resultDataWidget.hpp"

#include <sstream>

namespace ble::gui::widgets {

ResultDataWidget::ResultDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ResultData)
{
    ui->setupUi(this);

    connect(ui->Slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderValueChange()));
}

void ResultDataWidget::setData(
    const std::shared_ptr<ble_src::calc::models::BleResultData> data,
    std::function<void(double)> progress)
{
    _data = data;
    // clear all;
    ui->Slider->setValue(1);
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
    const std::shared_ptr<ble_src::common::models::DynamicData> d)
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

}
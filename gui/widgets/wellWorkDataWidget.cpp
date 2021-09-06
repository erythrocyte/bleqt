#include "wellWorkDataWidget.hpp"

#include "logging/logger.hpp"
#include <sstream>

ble_gui::widgets::WellWorkDataWidget::WellWorkDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::WellWorkData)
{
    ui->setupUi(this);
    ui->Chart->setTitle("Well work parameters");
}

void ble_gui::widgets::WellWorkDataWidget::setData(
    const std::vector<std::shared_ptr<ble_src::common::models::WellWorkParams>>& data)
{
    ble_src::logging::write_log("well work data set begins", ble_src::logging::kDebug);
    ui->SeriesQliq->clear();
    ui->SeriesQwat->clear();
    ui->SeriesQoil->clear();
    ui->SeriesFw->clear();

    for (auto& d : data) {
        ui->SeriesFw->append(d->t, d->fw);
        ui->SeriesQliq->append(d->t, d->ql);
        ui->SeriesQoil->append(d->t, d->qo);
        ui->SeriesQwat->append(d->t, d->qw);
    }

    ble_src::logging::write_log("well work data set ends", ble_src::logging::kDebug);
}

void ble_gui::widgets::WellWorkDataWidget::set_xrange(double max_value)
{
    ui->setup_xaxis_max(max_value);
}

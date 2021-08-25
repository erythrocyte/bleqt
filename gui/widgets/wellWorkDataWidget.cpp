#include "wellWorkDataWidget.hpp"

#include <sstream>

ble_gui::widgets::WellWorkDataWidget::WellWorkDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::WellWorkData)
{
    ui->setupUi(this);
    ui->Chart->setTitle("Well work parameters");
}

void ble_gui::widgets::WellWorkDataWidget::setData(
    const std::shared_ptr<ble_src::calc::models::BleResultData> data)
{
    ui->SeriesQliq->clear();
    ui->SeriesQwat->clear();
    ui->SeriesQoil->clear();
    ui->SeriesFw->clear();

    // for (auto& cl : _data->grd->cells) {
    //     ui->SeriesPress->append(cl->cntr, d->p[cl->ind]);
    //     ui->SeriesSatNum->append(cl->cntr, d->s[cl->ind]);
    // }

    // for (auto& v : d->s_an) {
    //     double x1, s1;
    //     std::tie(x1, s1) = v;
    //     ui->SeriesSatAn->append(x1, s1);
    // }
}
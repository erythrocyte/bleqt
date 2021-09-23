/*
 * Filename: wellWorkDataWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Sunday, September 19th 2021, 10:46:09 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "wellWorkDataWidget.hpp"

#include "logging/logger.hpp"
#include <sstream>

namespace ble_gui::widgets {

WellWorkDataWidget::WellWorkDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::WellWorkData)
{
    ui->setupUi(this);
    ui->Chart->setTitle("Well work parameters");
    subsribe();
}

void WellWorkDataWidget::setData(
    const std::vector<std::shared_ptr<ble_src::common::models::WellWorkParams>>& data)
{
    ble_src::logging::write_log("well work data set begins", ble_src::logging::kDebug);

    ui->create_series();

    for (auto& d : data) {
        ui->SeriesFw->append(d->t, d->fw);
        ui->SeriesQliq->append(d->t, d->ql);
        ui->SeriesQoil->append(d->t, d->qo);
        ui->SeriesQwat->append(d->t, d->qw);
    }

    ui->add_series();

    ble_src::logging::write_log("well work data set ends", ble_src::logging::kDebug);
}

void WellWorkDataWidget::set_xrange(double max_value)
{
    ui->setup_xaxis_max(max_value);
}

void WellWorkDataWidget::subsribe()
{
    auto success = QObject::connect(ui->ShowTable, SIGNAL(triggered()), this, SLOT(handleShowHideTable()));
    Q_ASSERT(success);
}

void WellWorkDataWidget::handleShowHideTable()
{
    if (ui->Table->isHidden()) {
        ui->Table->show();
        ui->ShowTable->setText("&Hide table");
    } else {
        ui->Table->hide();
        ui->ShowTable->setText("&Show table");
    }
}

}

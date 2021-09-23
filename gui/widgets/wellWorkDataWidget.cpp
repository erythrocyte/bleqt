/*
 * Filename: wellWorkDataWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Sunday, September 19th 2021, 10:46:09 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "wellWorkDataWidget.hpp"

#include <sstream>

#include <QVXYModelMapper>

#include "logging/logger.hpp"

namespace ble::gui::widgets {

WellWorkDataWidget::WellWorkDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::WellWorkData)
{
    ui->setupUi(this);
    ui->Chart->setTitle("Well work parameters");
    subsribe();
}

WellWorkDataWidget::~WellWorkDataWidget()
{
    delete ui;
    delete m_model;
}

void WellWorkDataWidget::set_data(models::WellWorkParamsModel* model)
{
    ble_src::logging::write_log("well work data set begins", ble_src::logging::kDebug);
    m_model = model;

    // ui->create_series();

    // for (auto& d : data) {
    //     ui->SeriesFw->append(d->t, d->fw);
    //     ui->SeriesQliq->append(d->t, d->ql);
    //     ui->SeriesQoil->append(d->t, d->qo);
    //     ui->SeriesQwat->append(d->t, d->qw);
    // }

    // ui->add_series();

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

void WellWorkDataWidget::fill_table()
{
}

void WellWorkDataWidget::fill_chart()
{
    // ui->create_series();

    ui->Chart->removeAllSeries();

    QVXYModelMapper* mapper = new QVXYModelMapper(this);

    for (int k = 1; k < m_model->columnCount(m_model->index(0, 0)); k++) {
        mapper->setXColumn(0);
        mapper->setYColumn(k);
        QString name = m_model->headerData(k, Qt::Horizontal, Qt::DisplayRole).toString();
        auto series = ui->create_series(name);
        mapper->setSeries(series.get());
        mapper->setModel(m_model);
        bool is_left = true;
        ui->add_series(series, is_left);
    }

    // for (auto& d : data) {
    //     ui->SeriesFw->append(d->t, d->fw);
    //     ui->SeriesQliq->append(d->t, d->ql);
    //     ui->SeriesQoil->append(d->t, d->qo);
    //     ui->SeriesQwat->append(d->t, d->qw);
    // }

    // ui->add_series();
}

}

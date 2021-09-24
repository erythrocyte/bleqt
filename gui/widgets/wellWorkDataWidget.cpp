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

#include <QHeaderView>
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
    ble::src::logging::write_log("well work data set begins", ble::src::logging::kDebug);
    m_model = model;

    fill_table();
    fill_chart();

    ble::src::logging::write_log("well work data set ends", ble::src::logging::kDebug);
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
    ui->Table->setModel(m_model);
    ui->Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void WellWorkDataWidget::fill_chart()
{
    ui->Chart->removeAllSeries();

    for (int k = 1; k < m_model->columnCount(); k++) { //k = 0 is x axis;
        QVXYModelMapper* mapper = new QVXYModelMapper(this);
        mapper->setXColumn(0); // x axis;
        mapper->setYColumn(k);
        QString name = m_model->headerData(k, Qt::Horizontal, Qt::DisplayRole).toString();
        auto series = ui->create_series(name);        
        mapper->setSeries(series);
        mapper->setModel(m_model);
        bool is_left = m_model->is_yaxis_left(k);
        ui->add_series(series, is_left);
    }

    ui->set_min_q(0.0);
}

}

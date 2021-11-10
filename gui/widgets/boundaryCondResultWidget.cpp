/*
 * Filename: boundaryCondResultWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Monday, September 27th 2021, 7:44:17 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "boundaryCondResultWidget.hpp"

#include "logging/logger.hpp"

#include <QHeaderView>
#include <QVXYModelMapper>

namespace ble::gui::widgets {

TopBotBoundWidget::TopBotBoundWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::BoundaryCondResult)
{
    ui->setupUi(this);
    ui->Chart->setTitle("RHS");
    subsribe();
}

TopBotBoundWidget::~TopBotBoundWidget()
{
    delete ui;
    delete m_model;
}

void TopBotBoundWidget::set_data(models::TopBotBoundUModel* model)
{
    src::logging::write_log("rhs data set begins", ble::src::logging::kDebug);
    m_model = model;

    fill_table();
    fill_chart();

    src::logging::write_log("rhs data set ends", ble::src::logging::kDebug);
}

void TopBotBoundWidget::set_xrange(double max_value)
{
    ui->setup_xaxis_max(max_value);
}

void TopBotBoundWidget::subsribe()
{
    auto success = QObject::connect(ui->ShowTable, SIGNAL(triggered()), this, SLOT(handleShowHideTable()));
    Q_ASSERT(success);
}

void TopBotBoundWidget::handleShowHideTable()
{
    if (ui->Table->isHidden()) {
        ui->Table->show();
        ui->ShowTable->setText("&Hide table");
    } else {
        ui->Table->hide();
        ui->ShowTable->setText("&Show table");
    }
}

void TopBotBoundWidget::fill_table()
{
    ui->Table->setModel(m_model);
    ui->Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void TopBotBoundWidget::fill_chart()
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
        ui->add_series(series);
    }

    double min_value, max_value;
    std::tie(min_value, max_value) = m_model->getValueRange();
    if (std::abs(min_value - max_value) < 1e-6)
    {
        min_value = min_value * 0.95;
        max_value = max_value * 1.05;
    }
    ui->setup_yaxis_range(min_value, max_value);
}

} // namespace ble_gui::widgets

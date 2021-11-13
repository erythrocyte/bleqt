/*
 * Filename: boundaryCondResultWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Monday, September 27th 2021, 7:44:17 am
 * Author: erythrocyte
 *
 * Copyright (c) 2021 Your Company
 */

#include "boundVisualWidget.hpp"

#include "logging/logger.hpp"

#include <QHeaderView>
#include <QVXYModelMapper>

namespace ble::gui::widgets {

BoundVisualWidget::BoundVisualWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::BoundVisual)
{
    ui->setupUi(this);
    ui->Chart->setTitle("RHS");
    subsribe();
}

BoundVisualWidget::~BoundVisualWidget()
{
    delete ui;
    delete m_model;
}

void BoundVisualWidget::set_data(models::BoundModel* model)
{
    src::logging::write_log("rhs data set begins", ble::src::logging::kDebug);
    m_model = model;

    fill_table();
    fill_chart();

    src::logging::write_log("rhs data set ends", ble::src::logging::kDebug);
}

void BoundVisualWidget::set_xrange(double max_value)
{
    ui->setup_xaxis_max(max_value);
}

void BoundVisualWidget::subsribe()
{
    auto success = QObject::connect(ui->ShowTable, SIGNAL(triggered()), this, SLOT(handleShowHideTable()));
    Q_ASSERT(success);
}

void BoundVisualWidget::handleShowHideTable()
{
    if (ui->Table->isHidden()) {
        ui->Table->show();
        ui->ShowTable->setText("&Hide table");
    } else {
        ui->Table->hide();
        ui->ShowTable->setText("&Show table");
    }
}

void BoundVisualWidget::fill_table()
{
    ui->Table->setModel(m_model);
    ui->Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void BoundVisualWidget::fill_chart()
{
    ui->Chart->removeAllSeries();
    double min_value, max_value;

    for (int k = 1; k < m_model->columnCount(); k++) { // k = 0 is x axis;
        QVXYModelMapper* mapper = new QVXYModelMapper(this);
        mapper->setXColumn(0); // x axis;
        mapper->setYColumn(k);
        QString name = m_model->headerData(k, Qt::Horizontal, Qt::DisplayRole).toString();
        auto series = ui->create_series(name);
        mapper->setSeries(series);
        mapper->setModel(m_model);
        ui->add_series(series);

        std::tie(min_value, max_value) = m_model->getValueRange(k);
        if (std::abs(min_value - max_value) < 1e-6) {
            min_value = min_value * 0.95;
            max_value = max_value * 1.05;
        }

        ui->setup_yaxis_range(min_value, max_value);
    }
}

} // namespace ble_gui::widgets

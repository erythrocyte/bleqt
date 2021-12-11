#include "fwVisualWidget.hpp"

#include "common/models/commonVals.hpp"
#include "logging/logger.hpp"

#include <QHeaderView>
#include <QVXYModelMapper>

namespace ble::gui::widgets {

FwVisualWidget::FwVisualWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::FwVisual)
{
    ui->setupUi(this);
    subsribe();
}

FwVisualWidget::~FwVisualWidget()
{
    delete ui;
    delete m_model;
}

void FwVisualWidget::set_data(models::FwModel* model)
{
    ui->Chart->series().clear();
    m_model = model;

    fill_table();
    fill_chart();
}

void FwVisualWidget::set_xrange(double max_value)
{
    ui->setup_xaxis_max(max_value);
}

void FwVisualWidget::subsribe()
{
    auto success = QObject::connect(ui->ShowTable, SIGNAL(triggered()), this, SLOT(handleShowHideTable()));
    Q_ASSERT(success);
}

void FwVisualWidget::handleShowHideTable()
{
    if (ui->Table->isHidden()) {
        ui->Table->show();
        ui->ShowTable->setText("&Hide table");
    } else {
        ui->Table->hide();
        ui->ShowTable->setText("&Show table");
    }
}

void FwVisualWidget::fill_table()
{
    ui->Table->setModel(m_model);
    ui->Table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void FwVisualWidget::fill_chart()
{
    ui->Chart->removeAllSeries();
    double min_value, max_value;
    std::tie(min_value, max_value) = m_model->get_value_range(0); // x axis
    ui->setup_xaxis_max(max_value);

    for (int k = 1; k < m_model->columnCount(); k++) { // k = 0 is x axis;
        if (k == 2)
            continue;
        std::tie(min_value, max_value) = m_model->get_value_range(k);
        if (src::common::models::CommonVals::is_empty(min_value) && src::common::models::CommonVals::is_empty(max_value))
            continue;
        QVXYModelMapper* mapper = new QVXYModelMapper(this);
        mapper->setXColumn(0); // x axis;
        mapper->setYColumn(k);
        QString name = m_model->headerData(k, Qt::Horizontal, Qt::DisplayRole).toString();
        auto series = ui->create_series(name);
        mapper->setSeries(series);
        mapper->setModel(m_model);
        ui->add_series(series, k);
        ui->setup_yaxis_range(min_value, max_value, k);
    }
}

} // namespace ble_gui::widgets

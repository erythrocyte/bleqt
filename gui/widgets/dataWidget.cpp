#include "dataWidget.hpp"

#include <QVBoxLayout>

namespace ble::gui::widgets {

DataWidget::DataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::Data)
{
    ui->setupUI(this);
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::set_view_objects(std::shared_ptr<models::DataWidgetComponentsDto> components)
{
    ui->MainLayout->addWidget(components->geom_widget.get());
    ui->MainLayout->addWidget(components->geol_widget.get());
    ui->MainLayout->addWidget(components->relperm_widget.get());
    ui->MainLayout->addWidget(components->modeldata_widget.get());
    ui->MainLayout->addWidget(components->satsolverset_view.get());
    ui->MainLayout->addWidget(components->gridset_widget.get());
    ui->MainLayout->addWidget(components->shockfront_widget.get());
    ui->MainLayout->addWidget(components->cond_widget.get());
}
}

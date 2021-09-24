#include "dataWidget.hpp"

#include <QVBoxLayout>

namespace ble::gui::widgets {

DataWidget::DataWidget(QWidget* parent)
    : QWidget(parent)
{
}

void DataWidget::set_view_objects(std::shared_ptr<models::DataWidgetComponentsDto> components)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(components->relperm_view.get());
    layout->addWidget(components->modeldata_view.get());
    layout->addWidget(components->satsolverset_view.get());
    layout->addWidget(components->gridset_view.get());
    layout->addWidget(components->shockfront_view.get());

    this->setLayout(layout);
}
}

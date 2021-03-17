#include "dataWidget.hpp"

#include <QVBoxLayout>

namespace ble_gui::widgets {

DataWidget::DataWidget(QWidget* parent)
    : QWidget(parent)
{
}

void ble_gui::widgets::DataWidget::set_view_objects(std::shared_ptr<models::DataWidgetComponentsDto> components)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(components->relperm_view.get());
    layout->addWidget(components->modeldata_view.get());
    layout->addWidget(components->satsolverset_view.get());
    layout->addWidget(components->gridset_view.get());

    // auto ShockFrontSetts = new ShockFrontSettsWidget();
    // layout->addWidget(ShockFrontSetts);

    this->setLayout(layout);
}
}

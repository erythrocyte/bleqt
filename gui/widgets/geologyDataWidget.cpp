#include "geologyDataWidget.hpp"


namespace ble::gui::widgets {

GeologyDataWidget::GeologyDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::GeologyData)
{
    ui->setupUi(this);

    subscribe();
}

void GeologyDataWidget::subscribe()
{
}

}
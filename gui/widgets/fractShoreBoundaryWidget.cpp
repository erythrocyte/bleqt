#include "fractShoreBoundaryWidget.hpp"

namespace ble::gui::widgets {

FractShoreWidget::FractShoreWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::FractShore)
{
    ui->setupUi(this);

    subscribe();
}

void FractShoreWidget::subscribe()
{
}

}
#include "dimlesParamsWidget.hpp"

namespace ble::gui::widgets {

DimlesParamsWidget::DimlesParamsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::DimlessParams)
{
    ui->setupUi(this);
}

void DimlesParamsWidget::set_mvalue(double value)
{
    ui->valueM->setText("M = " + QString::number(value));
}

} // namespace ble_gui::widgets

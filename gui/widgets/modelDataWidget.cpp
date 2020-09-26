#include "modelDataWidget.hpp"

ble_gui::widgets::ModelDataWidget::ModelDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ModelData)
{
    ui->setupUi(this);
}

double ble_gui::widgets::ModelDataWidget::getModelingPeriod()
{
    return ui->Period->value();
}

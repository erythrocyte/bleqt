#include "shockFrontSettsWidget.hpp"

ble_gui::widgets::ShockFrontSettsWidget::ShockFrontSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ShockFrontSetts)
{
    ui->setupUi(this);

    connect(ui->showCurve, SIGNAL(stateChanged(int)), this, SLOT(changeCheckStatus()));
}

void ble_gui::widgets::ShockFrontSettsWidget::SetShockFrontValue(std::string value)
{
    ui->shockFrontValue->setText(QString::fromStdString(value));
}

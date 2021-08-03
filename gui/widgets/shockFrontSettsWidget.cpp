#include "shockFrontSettsWidget.hpp"

namespace ble_gui::widgets {
ShockFrontSettsWidget::ShockFrontSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ShockFrontSetts)
{
    ui->setupUi(this);

    connect(ui->showCurve, SIGNAL(stateChanged(int)), this, SLOT(changeCheckStatus()));
}

void ShockFrontSettsWidget::SetShockFrontValue(double value)
{
    ui->shockFrontValue->setText(QString::number(value));
}

void ShockFrontSettsWidget::set_show_shockfront_status(bool status)
{
    ui->showCurve->setChecked(status);
    emit showShockFrontCurve(ui->showCurve->isChecked());
}

}

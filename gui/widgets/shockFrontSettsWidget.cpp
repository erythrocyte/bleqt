#include "shockFrontSettsWidget.hpp"

namespace ble::gui::widgets {
ShockFrontSettsWidget::ShockFrontSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ShockFrontSetts)
{
    ui->setupUi(this);

    connect(ui->showCurve, SIGNAL(stateChanged(int)), this, SLOT(changeCheckStatus()));
}

void ShockFrontSettsWidget::SetShockFrontValue(double value)
{
    ui->shockFrontValue->setText("Value = " + QString::number(value));
}

void ShockFrontSettsWidget::set_show_shockfront_status(bool status)
{
    ui->showCurve->setChecked(status);
    emit showShockFrontCurve(ui->showCurve->isChecked());
}

void ShockFrontSettsWidget::set_block(bool status)
{
    if (status) {
        ui->showCurve->setCheckState(Qt::CheckState::Unchecked);
        ui->shockFrontValue->setText("");
    }

    ui->showCurve->setEnabled(status);
    ui->shockFrontValue->setEnabled(status);
}

}

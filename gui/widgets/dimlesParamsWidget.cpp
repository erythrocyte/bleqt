#include "dimlesParamsWidget.hpp"

namespace ble::gui::widgets {

DimlesParamsWidget::DimlesParamsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::DimlessParams)
{
    ui->setupUi(this);
}

void DimlesParamsWidget::set_params(const std::shared_ptr<models::DimlessParamsDto> params)
{
    ui->valueM->setText("M = " + QString::number(params->m));
    ui->valueL->setText("L = " + QString::number(params->l));
    ui->valueR->setText("Rc = " + QString::number(params->r));
    ui->valueRw->setText("Rw = " + QString::number(params->rw));
    ui->valuePoro->setText("Poro = " + QString::number(params->poro));
    ui->valueKmu->setText("Kmu = " + QString::number(params->kmu));
    ui->valueEps->setText("Eps = " + QString::number(params->eps));
    ui->valueRpN->setText("RpN = " + QString::number(params->rp_n));
}

} // namespace ble_gui::widgets

#include "dataWidget.hpp"

#include <QVBoxLayout>

namespace ble::gui::widgets {

DataWidget::DataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::Data)
{
    ui->setupUI(this);
    subscribe();
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::subscribe()
{
    auto success = connect(ui->N, SIGNAL(valueChanged(double)), this, SLOT(rp_values_changed()));
    Q_ASSERT(success);
    success = connect(ui->MuWat, SIGNAL(valueChanged(double)), this, SLOT(rp_values_changed()));
    Q_ASSERT(success);
    success = connect(ui->MuOil, SIGNAL(valueChanged(double)), this, SLOT(rp_values_changed()));
    Q_ASSERT(success);
    success = connect(ui->UseFwLimit, &QCheckBox::toggled, this, &DataWidget::use_fw_limit_toogled);
    Q_ASSERT(success);
}

std::shared_ptr<ble::src::common::models::Data> DataWidget::get_data()
{
    auto result = std::make_shared<ble::src::common::models::Data>();

    // geom
    result->delta = ui->Delta->value();
    result->l = ui->L->value();
    result->r = ui->R->value();
    result->rw = ui->Rw->value();

    // geol
    result->perm_res = ui->Perm->value();
    result->poro_fract = ui->PoroFract->value();
    result->perm_fract = ui->PermFract->value();

    // model
    result->period = ui->Period->value();
    result->fw_lim = ui->FwLimit->value();
    result->use_fwlim = ui->UseFwLimit->isChecked();

    // rel perm
    result->phys = std::make_shared<ble::src::common::models::PhysData>();
    result->phys->mu_oil = ui->MuOil->value();
    result->phys->mu_wat = ui->MuWat->value();
    result->phys->n_oil = ui->N->value();
    result->phys->n_wat = ui->N->value();

    return result;
}

void DataWidget::use_fw_limit_toogled(bool state)
{
    ui->FwLimit->setEnabled(state);
    ui->Period->setEnabled(!state);
}

}

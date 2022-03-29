#include "dataWidget.hpp"

#include <QVBoxLayout>

namespace ble::gui::widgets {

DataWidget::DataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::Data)
{
    ui->setupUI(this);
    subscribe();

    ui->FwLimit->setValue(98);
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::subscribe()
{
    // fluid settings
    auto success = connect(ui->N, SIGNAL(valueChanged(int)), this, SLOT(rp_values_changed()));
    Q_ASSERT(success);
    success = connect(ui->MuWat, SIGNAL(valueChanged(double)), this, SLOT(rp_values_changed()));
    Q_ASSERT(success);
    success = connect(ui->MuOil, SIGNAL(valueChanged(double)), this, SLOT(rp_values_changed()));
    Q_ASSERT(success);

    // dimless parameters;
    success = connect(ui->Delta, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);
    success = connect(ui->L, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);
    success = connect(ui->Perm, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);
    success = connect(ui->PermFract, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);
    success = connect(ui->R, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);
    success = connect(ui->Rw, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);
    success = connect(ui->PoroFract, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DataWidget::dimless_params_changed);
    Q_ASSERT(success);

    // other
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
    result->phys = std::make_shared<ble::src::common::models::PhysData>(
        ui->N->value(),
        ui->N->value(),
        ui->MuWat->value(),
        ui->MuOil->value());

    return result;
}

void DataWidget::use_fw_limit_toogled(bool state)
{
    ui->FwLimit->setEnabled(state);
    ui->Period->setEnabled(!state);
}

}

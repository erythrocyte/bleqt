#include "satSolverSettsWidget.hpp"

#include "calc/models/saturSolverType.hpp"

namespace sclcm = ble::src::calc::models;

namespace ble::gui::widgets {

SatSolverSettsWidget::SatSolverSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::SatSolverSetts)
{
    ui->setupUi(this);
    for (sclcm::SaturSolverType::TypeEnum v : sclcm::SaturSolverTypeEnumIterator()) {
        ui->SolverType->addItem(
            QString::fromStdString(sclcm::SaturSolverType::get_description(v)));
    }

    subscribe();
    need_stop_fw_shorewell_converge(false);
}

std::shared_ptr<src::calc::models::SaturSolverSetts> SatSolverSettsWidget::get_data()
{
    auto result = std::make_shared<src::calc::models::SaturSolverSetts>();
    result->cv = ui->CurantVolume->value();
    result->cg = ui->CurantFace->value();
    result->need_satur_solve = ui->NeedSaturSolve->isChecked();
    result->pressure_update_n = ui->RecalcPressN->value();
    result->satur_field_save_n = ui->SaveSaturField->value();
    result->max_iter = ui->MaxIter->value();

    result->use_fw_delta = ui->NeedStopFwPseudoConst->isChecked();
    result->fw_delta = ui->FwDelta->value();
    result->fw_delta_iter = ui->FwDeltaIter->value();

    result->use_fw_shorewell_converge = ui->NeedStopFwShoreWellConverge->isChecked();
    result->fw_shw_conv = ui->FwShoreWellConverge->value();

    auto str = ui->SolverType->currentText().toStdString();
    result->type = src::calc::models::SaturSolverType::get_enum(str);

    return result;
}

void SatSolverSettsWidget::subscribe()
{
    auto success = connect(ui->NeedStopFwPseudoConst, &QCheckBox::toggled, this, &SatSolverSettsWidget::need_stop_fw_pseudo_const);
    Q_ASSERT(success);
    success = connect(ui->NeedStopFwShoreWellConverge, &QCheckBox::toggled, this, &SatSolverSettsWidget::need_stop_fw_shorewell_converge);
    Q_ASSERT(success);
}

void SatSolverSettsWidget::need_stop_fw_pseudo_const(bool state)
{
    ui->FwDelta->setEnabled(state);
    ui->FwDeltaIter->setEnabled(state);
}

void SatSolverSettsWidget::need_stop_fw_shorewell_converge(bool state)
{
    ui->FwShoreWellConverge->setEnabled(state);
}

}

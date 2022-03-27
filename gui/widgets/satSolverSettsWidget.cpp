#include "satSolverSettsWidget.hpp"

#include "calc/models/saturSolverType.hpp"
#include "common/models/timeStepType.hpp"

namespace sclcm = ble::src::calc::models;
namespace scm = ble::src::common::models;

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

    bool isExplicit = false;
    make_solver_type_change(isExplicit);
    for (scm::TimeStepType::TypeEnum v : scm::TimeStepTypeEnumIterator()) {
        ui->TimeStepType->addItem(QString::fromStdString(scm::TimeStepType::get_description(v)));
    }

    ui->MaxIter->setValue(10000);
    ui->TimeStepType->setCurrentIndex(0);
    ui->SolverType->setCurrentIndex(1);

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

    result->tau = ui->TauForFim->value();
    result->simple_iter_count = ui->SimpleIterCount->value();
    result->use_fw_shorewell_converge = ui->NeedStopFwShoreWellConverge->isChecked();
    result->fw_shw_conv = ui->FwShoreWellConverge->value();

    auto str = ui->SolverType->currentText().toStdString();
    result->type = src::calc::models::SaturSolverType::get_enum(str);

    str = ui->TimeStepType->currentText().toStdString();
    result->time_step_type = src::common::models::TimeStepType::get_enum(str);

    return result;
}

void SatSolverSettsWidget::subscribe()
{
    auto success = connect(ui->NeedStopFwPseudoConst, &QCheckBox::toggled, this, &SatSolverSettsWidget::need_stop_fw_pseudo_const);
    Q_ASSERT(success);
    success = QObject::connect(ui->SolverType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_solver_type_changed(int)));
    Q_ASSERT(success);
    success = connect(ui->NeedStopFwShoreWellConverge, &QCheckBox::toggled, this, &SatSolverSettsWidget::need_stop_fw_shorewell_converge);
    Q_ASSERT(success);
}

void SatSolverSettsWidget::need_stop_fw_pseudo_const(bool state)
{
    ui->FwDelta->setEnabled(state);
    ui->FwDeltaIter->setEnabled(state);
}

void SatSolverSettsWidget::on_solver_type_changed(int index)
{
    make_solver_type_change(index == 0); // 0 is explicit
}

void SatSolverSettsWidget::make_solver_type_change(bool isExplicit)
{
    ui->TauForFim->setEnabled(!isExplicit);
    ui->SimpleIterCount->setEnabled(!isExplicit);

    ui->CurantFace->setEnabled(isExplicit);
    ui->CurantVolume->setEnabled(isExplicit);
}

void SatSolverSettsWidget::need_stop_fw_shorewell_converge(bool state)
{
    ui->FwShoreWellConverge->setEnabled(state);
}

}

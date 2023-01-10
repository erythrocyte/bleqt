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
        ui->solver_type->addItem(
            QString::fromStdString(sclcm::SaturSolverType::get_description(v)));
    }

    bool isExplicit = false;
    make_solver_type_change(isExplicit);
    for (scm::TimeStepType::TypeEnum v : scm::TimeStepTypeEnumIterator()) {
        ui->time_step_type->addItem(QString::fromStdString(scm::TimeStepType::get_description(v)));
    }

    ui->max_iter->setValue(10000);
    ui->time_step_type->setCurrentIndex(0);
    ui->solver_type->setCurrentIndex(1);

    subscribe();
    need_stop_fw_shorewell_converge(false);
}

std::shared_ptr<src::calc::models::SaturSolverSetts> SatSolverSettsWidget::get_data()
{
    auto result = std::make_shared<src::calc::models::SaturSolverSetts>();
    result->cv = ui->curant_volume->value();
    result->cg = ui->curant_face->value();
    result->need_satur_solve = ui->need_satur_solve->isChecked();
    result->pressure_update_n = ui->recalc_press_n->value();
    result->satur_field_save_n = ui->fix_fields_step->value();
    result->max_iter = ui->max_iter->value();

    result->use_fw_delta = ui->need_stop_fw_converge->isChecked();
    result->fw_delta = ui->fw_converge_delta->value();
    result->fw_delta_iter = ui->fw_converge_iter->value();

    result->tau = ui->impl_tau->value();
    result->simple_iter_count = ui->impl_simple_iter_count->value();
    result->use_fw_shorewell_converge = ui->need_stop_fw_shore_well_converge->isChecked();
    result->fw_shw_conv = ui->fw_shore_well_converge_value->value();

    auto str = ui->solver_type->currentText().toStdString();
    result->type = src::calc::models::SaturSolverType::get_enum(str);

    str = ui->time_step_type->currentText().toStdString();
    result->time_step_type = src::common::models::TimeStepType::get_enum(str);

    return result;
}

void SatSolverSettsWidget::subscribe()
{
    auto success = connect(ui->need_stop_fw_converge, &QCheckBox::toggled, this, &SatSolverSettsWidget::need_stop_fw_pseudo_const);
    Q_ASSERT(success);
    success = QObject::connect(ui->solver_type, SIGNAL(currentIndexChanged(int)), this, SLOT(on_solver_type_changed(int)));
    Q_ASSERT(success);
    success = connect(ui->need_stop_fw_shore_well_converge, &QCheckBox::toggled, this, &SatSolverSettsWidget::need_stop_fw_shorewell_converge);
    Q_ASSERT(success);

    //     success = connect(ui->UseFwLimit, &QCheckBox::toggled, this, &DataWidget::use_fw_limit_toogled);
    // Q_ASSERT(success);
}

void SatSolverSettsWidget::need_stop_fw_pseudo_const(bool state)
{
    ui->fw_converge_delta->setEnabled(state);
    ui->fw_converge_iter->setEnabled(state);
}

void SatSolverSettsWidget::on_solver_type_changed(int index)
{
    make_solver_type_change(index == 0); // 0 is explicit
}

void SatSolverSettsWidget::make_solver_type_change(bool isExplicit)
{
    ui->impl_tau->setEnabled(!isExplicit);
    ui->impl_simple_iter_count->setEnabled(!isExplicit);

    ui->time_step_type->setEnabled(isExplicit);
    ui->curant_face->setEnabled(isExplicit);
    ui->curant_volume->setEnabled(isExplicit);
}

void SatSolverSettsWidget::need_stop_fw_shorewell_converge(bool state)
{
    ui->fw_shore_well_converge_value->setEnabled(state);
}

// void DataWidget::use_fw_limit_toogled(bool state)
// {
//     ui->FwLimit->setEnabled(state);
//     ui->Period->setEnabled(!state);
// }

}

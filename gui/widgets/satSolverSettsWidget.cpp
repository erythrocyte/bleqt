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
}

std::shared_ptr<src::calc::models::SaturSolverSetts> SatSolverSettsWidget::get_data()
{
    auto result = std::make_shared<src::calc::models::SaturSolverSetts>();
    result->cur_val = ui->Curant->value();
    result->need_satur_solve = ui->NeedSaturSolve->isChecked();
    result->pressure_update_n = ui->RecalcPressN->value();
    result->satur_field_save_n = ui->SaveSaturField->value();

    auto str = ui->SolverType->currentText().toStdString();
    result->type = src::calc::models::SaturSolverType::get_enum(str);

    return result;
}

}

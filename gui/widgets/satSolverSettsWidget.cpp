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

src::calc::models::SaturSolverType::TypeEnum SatSolverSettsWidget::solver_type()
{
    auto str = ui->SolverType->currentText().toStdString();
    return src::calc::models::SaturSolverType::get_enum(str);
}

}

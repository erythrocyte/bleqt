#include "satSolverSettsWidget.hpp"

#include "calc/models/saturSolverType.hpp"

namespace ble::gui::widgets {

SatSolverSettsWidget::SatSolverSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::SatSolverSetts)
{
    ui->setupUi(this);
    for (ble_src::calc::models::SaturSolverType::TypeEnum v : ble_src::calc::models::SaturSolverTypeEnumIterator()) {
        ui->SolverType->addItem(
            QString::fromStdString(ble_src::calc::models::SaturSolverType::get_description(v)));
    }
}

}

#include "satSolverSettsWidget.hpp"

#include "saturSolverType.hpp"

namespace ble_gui::widgets {

SatSolverSettsWidget::SatSolverSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::SaturSolverSetts)
{
    ui->setupUi(this);
    for (ble_src::SaturSolverType::TypeEnum v : ble_src::SaturSolverTypeEnumIterator()) {
        ui->SolverType->addItem(
            QString::fromStdString(ble_src::SaturSolverType::get_description(v)));
    }
}

}

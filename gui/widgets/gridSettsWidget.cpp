#include "gridSettsWidget.hpp"

#include "common/models/gridType.hpp"

namespace ble::gui::widgets {

GridSettsWidget::GridSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::GridSetts)
{
    ui->setupUI(this);
    for (scm::GridType::TypeEnum v : scm::GridTypeEnumIterator()) {
        ui->GridType->addItem(QString::fromStdString(scm::GridType::get_description(v)));
    }

    subscribe();
    fix_well_radius(ui->GridType->currentText());
}

void GridSettsWidget::gridTypeChanged(int index)
{
    fix_well_radius(ui->GridType->currentText());
}

void GridSettsWidget::subscribe()
{
    auto success = QObject::connect(ui->GridType, SIGNAL(currentIndexChanged(int)),
        this, SLOT(gridTypeChanged(int)));
    Q_ASSERT(success);
    success = QObject::connect(ui->CellCount, SIGNAL(valueChanged(int)), this, SLOT(onCellCountChanged(int)));
    Q_ASSERT(success);
}

void GridSettsWidget::fix_well_radius(const QString& txt)
{
    auto gridType = scm::GridType::get_enum(txt.toStdString());
    if (gridType == scm::GridType::kRegular) {
        ui->WellRadius->setValue(0.0);
    } else {
        ui->WellRadius->setValue(1e-3);
    }
}

scm::GridType::TypeEnum GridSettsWidget::get_grid_type()
{
    auto txt = ui->GridType->currentText();
    return scm::GridType::get_enum(txt.toStdString());
}

}
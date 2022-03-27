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

    ui->GridType->setCurrentIndex(1);
    ui->CellCount->setValue(200);

    subscribe();
}

void GridSettsWidget::subscribe()
{
    auto success = QObject::connect(ui->GridType, SIGNAL(currentIndexChanged(int)), this, SLOT(on_grid_type_changed(int)));
    Q_ASSERT(success);
    success = QObject::connect(ui->CellCount, SIGNAL(valueChanged(int)), this, SLOT(onCellCountChanged(int)));
    Q_ASSERT(success);
}

std::shared_ptr<scm::MeshSettings> GridSettsWidget::get_data()
{
    auto result = std::make_shared<scm::MeshSettings>();
    result->n = ui->CellCount->value();

    auto txt = ui->GridType->currentText();
    result->type = scm::GridType::get_enum(txt.toStdString());
    return result;
}

}
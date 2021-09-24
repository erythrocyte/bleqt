#include "gridSettsWidget.hpp"

#include "common/models/gridType.hpp"

namespace scm = ble::src::common::models;

namespace ble::gui::widgets {

GridSettsWidget::GridSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::GridSetts)
{
    ui->setupUI(this);
    for (scm::GridType::TypeEnum v : scm::GridTypeEnumIterator()) {
        ui->GridType->addItem(QString::fromStdString(scm::GridType::get_description(v)));
    }
}

}
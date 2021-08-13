#include "gridSettsWidget.hpp"

#include "common/models/gridType.hpp"

namespace ble_gui::widgets {

GridSettsWidget::GridSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::GridSetts)
{
    ui->setupUI(this);
    for (ble_src::common::models::GridType::TypeEnum v : ble_src::common::models::GridTypeEnumIterator()) {
        ui->GridType->addItem(QString::fromStdString(ble_src::common::models::GridType::get_description(v)));
    }
}

}
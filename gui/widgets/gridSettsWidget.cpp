#include "gridSettsWidget.hpp"

#include "gridType.hpp"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

ble_gui::widgets::GridSettsWidget::GridSettsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::GridSetts)
{
    ui->setupUI(this);
    for (ble_src::GridType::TypeEnum v : ble_src::GridTypeEnumIterator()) {
        ui->GridType->addItem(QString::fromStdString(ble_src::GridType::get_description(v)));
    }
}
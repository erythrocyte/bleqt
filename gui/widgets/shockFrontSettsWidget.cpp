#include "shockFrontSettsWidget.hpp"

#include <QGroupBox>
#include <QVBoxLayout>

ble_gui::widgets::ShockFrontSettsWidget::ShockFrontSettsWidget(QWidget* parent)
    : QWidget(parent)
{
    QGroupBox* groupBox = new QGroupBox("Shock front");
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(groupBox);
    QVBoxLayout* layout = new QVBoxLayout(groupBox);
    groupBox->setLayout(layout);

    shockFrontValue = new QLabel("");
    layout->addWidget(shockFrontValue);

    showCurve = new QCheckBox("Show shock front saturation");
    showCurve->setChecked(true);

    layout->addWidget(showCurve);
}

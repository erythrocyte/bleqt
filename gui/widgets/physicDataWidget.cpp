#include "physicDataWidget.hpp"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

void ble_gui::widgets::PhysDataWidget::addQDoubleSpinBoxLabel(QDoubleSpinBox* dSpinBox,
    double min, double max, double step, double value, int decimals,
    int spinboxRow, int spinboxCol, QLabel* label, int labelRow, int labelCol)
{
    dSpinBox->setMinimum(min);
    dSpinBox->setMaximum(max);
    dSpinBox->setSingleStep(step);
    dSpinBox->setDecimals(decimals);
    dSpinBox->setValue(value);

    ui->Layout->addWidget(label, labelRow, labelCol);
    ui->Layout->addWidget(dSpinBox, spinboxRow, spinboxCol);
}

ble_gui::widgets::PhysDataWidget::PhysDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::PhysicData)
{
    ui->setupUi(this);
    addQDoubleSpinBoxLabel(ui->Kmu, 0.1, 100, 0.1, 0.125, 3, 0, 1, ui->LabelKmu, 0, 0);
    addQDoubleSpinBoxLabel(ui->Nwat, 0.1, 10, 0.1, 2.0, 1, 1, 1, ui->LabelNwat, 1, 0);
    addQDoubleSpinBoxLabel(ui->Noil, 0.1, 10, 0.1, 2.0, 1, 2, 1, ui->LabelNoil, 2, 0);

    connect(ui->Noil, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
    connect(ui->Nwat, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
    connect(ui->Kmu, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
}

void ble_gui::widgets::PhysDataWidget::changeValues()
{
    emit valuesUpdated();
}

double ble_gui::widgets::PhysDataWidget::getKmu() const
{
    return ui->Kmu->value();
}

double ble_gui::widgets::PhysDataWidget::getNwat() const
{
    return ui->Nwat->value();
}

double ble_gui::widgets::PhysDataWidget::getNoil() const
{
    return ui->Noil->value();
}

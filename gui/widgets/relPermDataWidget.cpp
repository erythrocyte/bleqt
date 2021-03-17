#include "relPermDataWidget.hpp"

#include <QLabel>

namespace ble_gui::widgets {

RelPermDataWidget::RelPermDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::RelPermData)
{
    ui->setupUi(this);
    addQDoubleSpinBoxLabel(ui->Kmu, 0.1, 100, 0.1, 1.0, 1, 0, 1, ui->LabelKmu, 0, 0);
    addQDoubleSpinBoxLabel(ui->Nwat, 0.1, 10, 0.1, 3.0, 1, 1, 1, ui->LabelNwat, 1, 0);
    addQDoubleSpinBoxLabel(ui->Noil, 0.1, 10, 0.1, 3.0, 1, 2, 1, ui->LabelNoil, 2, 0);

    auto a = connect(ui->Noil, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
    connect(ui->Nwat, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
    connect(ui->Kmu, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
}

void RelPermDataWidget::addQDoubleSpinBoxLabel(QDoubleSpinBox* dSpinBox,
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

}
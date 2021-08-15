#include "relPermDataWidget.hpp"

#include <QLabel>

namespace ble_gui::widgets {

RelPermDataWidget::RelPermDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::RelPermData)
{
    ui->setupUi(this);
    addQDoubleSpinBoxLabel(ui->Kmu, 0.1, 100, 0.1, 1.0, 1, 0, 1, ui->LabelKmu, 0, 0);
    addQDoubleSpinBoxLabel(ui->N, 1.1, 5, 0.1, 3.0, 1, 1, 1, ui->LabelN, 1, 0);

    auto a = connect(ui->N, SIGNAL(valueChanged(double)), this, SLOT(changeValues()));
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
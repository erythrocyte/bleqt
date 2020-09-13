#include "physicDataWidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>

void addQDoubleSpinBoxLabel(QGridLayout *layout, QDoubleSpinBox *widget,
                            double min, double max,
                            double step, double value,
                            int decimals,
                            int spinboxRow, int spinboxCol,
                            QString labelCaption, int labelRow, int labelCol,
                            bool addWidget = true)
{
    // widget = new QDoubleSpinBox();
    widget->setMinimum(min);
    widget->setMaximum(max);
    widget->setSingleStep(step);
    widget->setDecimals(decimals);
    widget->setValue(value);

    if (addWidget)
        layout->addWidget(widget, spinboxRow, spinboxCol);

    QLabel *label = new QLabel(labelCaption);
    if (addWidget)
        layout->addWidget(label, labelRow, labelCol);
}

ble_gui::widgets::PhysDataWidget::PhysDataWidget(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *groupBox = new QGroupBox("Physical data");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(groupBox);
    QGridLayout *layout = new QGridLayout(groupBox);
    groupBox->setLayout(layout);

    layout->setMargin(5);

    Kmu = new QDoubleSpinBox();
    addQDoubleSpinBoxLabel(layout, Kmu, 0.1, 100, 0.1, 0.125, 3, 0, 1, tr("Kmu"), 0, 0);

    Nwat = new QDoubleSpinBox();
    addQDoubleSpinBoxLabel(layout, Nwat, 0.1, 10, 0.1, 2.0, 1, 1, 1, tr("Nwat"), 1, 0);

    Noil = new QDoubleSpinBox();
    addQDoubleSpinBoxLabel(layout, Noil, 0.1, 10, 0.1, 2.0, 1, 2, 1, tr("Noil"), 2, 0);

    Poro = new QDoubleSpinBox();
    addQDoubleSpinBoxLabel(layout, Poro, 0.1, 10000, 0.1, 1.0, 1, 3, 1, tr("Poro"), 3, 0, false);

    Perm = new QDoubleSpinBox();
    addQDoubleSpinBoxLabel(layout, Perm, 0.1, 10000, 0.1, 1.0, 1, 4, 1, tr("Perm"), 4, 0, false);
}

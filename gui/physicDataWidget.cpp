#include "physicDataWidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>

namespace ble_gui
{
    void addQDoubleSpinBoxLabel(QGridLayout *layout, QDoubleSpinBox *widget,
                                double min, double max,
                                double step, double value,
                                int decimals,
                                int spinboxRow, int spinboxCol,
                                QString labelCaption, int labelRow, int labelCol)
    {
        widget = new QDoubleSpinBox();
        widget->setMinimum(min);
        widget->setMaximum(max);
        widget->setSingleStep(step);
        widget->setDecimals(decimals);
        widget->setValue(value);

        layout->addWidget(widget, spinboxRow, spinboxCol);

        QLabel *label = new QLabel(labelCaption);
        layout->addWidget(label, labelRow, labelCol);
    }

    PhysDataWidget::PhysDataWidget(QWidget *parent)
    {
        QGroupBox* groupBox = new QGroupBox("Physical data");
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(groupBox);
        QGridLayout *layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

        addQDoubleSpinBoxLabel(layout, Kmu, 0.1, 100, 0.1, 0.125, 3, 0, 1, tr("Kmu"), 0, 0);
        addQDoubleSpinBoxLabel(layout, Nwat, 0.1, 10, 0.1, 2.0, 1, 1, 1, tr("Nwat"), 1, 0);
        addQDoubleSpinBoxLabel(layout, Noil, 0.1, 10, 0.1, 2.0, 1, 2, 1, tr("Noil"), 2, 0);
        addQDoubleSpinBoxLabel(layout, Poro, 0.1, 10000, 0.1, 1.0, 1, 3, 1, tr("Poro"), 3, 0);
        addQDoubleSpinBoxLabel(layout, Perm, 0.1, 10000, 0.1, 1.0, 1, 4, 1, tr("Perm"), 4, 0);
    }

} // namespace ble_gui

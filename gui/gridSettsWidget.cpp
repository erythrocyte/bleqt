#include "gridSettsWidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace ble_gui
{
    GridSettsWidget::GridSettsWidget(QWidget *parent)
    {
        QGroupBox *groupBox = new QGroupBox("Grid/Domain");
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(groupBox);
        QGridLayout *layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

        Length = new QDoubleSpinBox();
        Length->setMinimum(1);
        Length->setMaximum(1000);
        Length->setSingleStep(1.0);
        Length->setValue(1.0);
        layout->addWidget(Length, 0, 1);

        QLabel *lengthLabel = new QLabel("Length");
        layout->addWidget(lengthLabel, 0, 0);

        CellCount = new QSpinBox();
        CellCount->setMinimum(1);
        CellCount->setMaximum(10000);
        CellCount->setValue(100);
        layout->addWidget(CellCount, 1, 1);

        QLabel *cellCountLabel = new QLabel("Cell count");
        layout->addWidget(cellCountLabel, 1, 0);

        GridType = new QComboBox();
        layout->addWidget(GridType, 2, 1);

        QLabel *gridTypeLabel = new QLabel("Grid type");
        layout->addWidget(gridTypeLabel, 2, 0);
    }

} // namespace ble_gui
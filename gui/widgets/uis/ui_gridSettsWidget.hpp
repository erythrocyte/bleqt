#ifndef BLE_GUI_WIDGETS_UI_GRIDSETTS_H_
#define BLE_GUI_WIDGETS_UI_GRIDSETTS_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

namespace ble::gui::widgets::UI {

class GridSetts {

public:
    QDoubleSpinBox* WellRadius;
    QSpinBox* CellCount;
    QComboBox* GridType;

    void retranslateUi(QWidget* widget)
    {
        groupBox->setTitle("Grid/Domain");
        groupBox->setToolTip("Grid/Domain");

        wellRadiusLabel->setText("Well radius");
        wellRadiusLabel->setToolTip("Well radius");

        cellCountLabel->setText("Cell count");
        cellCountLabel->setToolTip("Cell count");

        gridTypeLabel->setText("Grid type");
        gridTypeLabel->setToolTip("Grid type");
    }

    void setupUI(QWidget* widget)
    {
        groupBox = new QGroupBox("Grid/Domain");
        mainLayout = new QVBoxLayout(widget);
        mainLayout->addWidget(groupBox);
        layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

        WellRadius = new QDoubleSpinBox();
        WellRadius->setMinimum(0.0);
        WellRadius->setMaximum(0.1);
        WellRadius->setSingleStep(1e-3);
        WellRadius->setValue(0.0);
        WellRadius->setDecimals(3);
        layout->addWidget(WellRadius, 0, 1);

        wellRadiusLabel = new QLabel("Well radius");
        layout->addWidget(wellRadiusLabel, 0, 0);

        CellCount = new QSpinBox();
        CellCount->setMinimum(1);
        CellCount->setMaximum(10000);
        CellCount->setValue(100);
        layout->addWidget(CellCount, 1, 1);

        cellCountLabel = new QLabel("Cell count");
        layout->addWidget(cellCountLabel, 1, 0);

        GridType = new QComboBox();
        layout->addWidget(GridType, 2, 1);

        gridTypeLabel = new QLabel("Grid type");
        layout->addWidget(gridTypeLabel, 2, 0);

        retranslateUi(widget);
    }

private:
    QGroupBox* groupBox;
    QVBoxLayout* mainLayout;
    QGridLayout* layout;
    QLabel* wellRadiusLabel;
    QLabel* cellCountLabel;
    QLabel* gridTypeLabel;
};

}

#endif
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
    QSpinBox* CellCount;
    QComboBox* GridType;

    void retranslateUi(QWidget* widget)
    {
        groupBox->setTitle("Settings");
        groupBox->setToolTip("Settings");

        cellCountLabel->setText("Cell count");
        cellCountLabel->setToolTip("Cell count");

        gridTypeLabel->setText("Grid type");
        gridTypeLabel->setToolTip("Grid type");
    }

    void setupUI(QWidget* widget)
    {
        groupBox = new QGroupBox("Settings");
        auto m_layout = new QVBoxLayout(widget);
        m_layout->addStretch();
        m_layout->setDirection(QVBoxLayout::BottomToTop);
        m_layout->addWidget(groupBox);
        widget->setLayout(m_layout);
        
        layout = new QGridLayout(groupBox);
        layout->setMargin(5);
        
        groupBox->setLayout(layout);
        layout->setMargin(5);

        CellCount = new QSpinBox();
        CellCount->setMinimum(1);
        CellCount->setMaximum(10000);
        CellCount->setValue(500);
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
    QGridLayout* layout;
    QLabel* cellCountLabel;
    QLabel* gridTypeLabel;
};

}

#endif
#ifndef BLEGUI_WIDGETS_UI_GRIDSETTS_H_
#define BLEGUI_WIDGETS_UI_GRIDSETTS_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

namespace ble_gui {
namespace widgets {

    namespace UI {

        class GridSetts {

        public:
            QDoubleSpinBox* Length;
            QSpinBox* CellCount;
            QComboBox* GridType;

            void retranslateUi(QWidget* widget)
            {
                groupBox->setTitle("Grid/Domain");
                groupBox->setToolTip("Grid/Domain");

                lengthLabel->setText("Length");
                lengthLabel->setToolTip("Length");

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

                Length = new QDoubleSpinBox();
                Length->setMinimum(1);
                Length->setMaximum(1000);
                Length->setSingleStep(1.0);
                Length->setValue(1.0);
                // layout->addWidget(Length, 0, 1);

                lengthLabel = new QLabel("Length");
                // layout->addWidget(lengthLabel, 0, 0);

                CellCount = new QSpinBox();
                CellCount->setMinimum(1);
                CellCount->setMaximum(10000);
                CellCount->setValue(100);
                layout->addWidget(CellCount, 1, 1);

                cellCountLabel = new QLabel("Cell count");
                layout->addWidget(cellCountLabel, 1, 0);

                GridType = new QComboBox();
                GridType->setEnabled(false);
                layout->addWidget(GridType, 2, 1);

                gridTypeLabel = new QLabel("Grid type");
                layout->addWidget(gridTypeLabel, 2, 0);

                retranslateUi(widget);
            }

        private:
            QGroupBox* groupBox;
            QVBoxLayout* mainLayout;
            QGridLayout* layout;
            QLabel* lengthLabel;
            QLabel* cellCountLabel;
            QLabel* gridTypeLabel;
        };
    }
}
}

#endif
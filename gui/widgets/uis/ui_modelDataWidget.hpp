#ifndef BLEGUI_WIDGETS_UI_MODELDATA_H_
#define BLEGUI_WIDGETS_UI_MODELDATA_H_

#include <iostream>
#include <memory>

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>

namespace ble_gui {
namespace widgets {
    namespace UI {

        class ModelData {
        private:
            QGroupBox* groupBox;
            QLabel* periodLabel;

        public:
            void retranslateUi(QWidget* widget)
            {
                groupBox->setTitle("Modeling data");
                groupBox->setToolTip("Modeling data");

                periodLabel->setText("Period");
                periodLabel->setToolTip("Period");
            }

            void setupUi(QWidget* widget)
            {
                groupBox = new QGroupBox("Modeling data");
                QVBoxLayout* mainLayout = new QVBoxLayout(widget);
                mainLayout->addWidget(groupBox);
                QGridLayout* layout = new QGridLayout(groupBox);
                groupBox->setLayout(layout);

                layout->setMargin(5);

                Period = new QDoubleSpinBox();
                Period->setMinimum(0.1);
                Period->setMaximum(1e10);
                Period->setSingleStep(0.1);
                Period->setValue(5);
                layout->addWidget(Period, 0, 1);

                periodLabel = new QLabel("Period");
                layout->addWidget(periodLabel, 0, 0);

                retranslateUi(widget);
            }

            QDoubleSpinBox* Period;
        };
    }
}
}

#endif

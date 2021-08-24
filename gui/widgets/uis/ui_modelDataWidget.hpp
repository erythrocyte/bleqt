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
            QGroupBox* m_groupBox;
            QLabel* m_periodLabel;
            QLabel* m_saveFieldStepsLabel;

        public:
            QDoubleSpinBox* Period;
            QDoubleSpinBox* SaveFieldSteps;

            void retranslateUi(QWidget* widget)
            {
                m_groupBox->setTitle("Modeling data");
                m_groupBox->setToolTip("Modeling data");

                m_periodLabel->setText("Period");
                m_periodLabel->setToolTip("Period");

                m_saveFieldStepsLabel->setText("Field step");
                m_saveFieldStepsLabel->setToolTip("Field step");
            }

            void setupUi(QWidget* widget)
            {
                m_groupBox = new QGroupBox("Modeling data");
                QVBoxLayout* mainLayout = new QVBoxLayout(widget);
                mainLayout->addWidget(m_groupBox);
                QGridLayout* layout = new QGridLayout(m_groupBox);
                m_groupBox->setLayout(layout);

                layout->setMargin(5);

                Period = new QDoubleSpinBox();
                Period->setMinimum(0.1);
                Period->setMaximum(1e10);
                Period->setSingleStep(0.1);
                Period->setValue(5);
                Period->setToolTip("Calculation time period");
                layout->addWidget(Period, 0, 1);

                m_periodLabel = new QLabel("Period");
                layout->addWidget(m_periodLabel, 0, 0);

                SaveFieldSteps = new QDoubleSpinBox();
                SaveFieldSteps->setMinimum(0.01);
                SaveFieldSteps->setMaximum(5);
                SaveFieldSteps->setSingleStep(0.01);
                SaveFieldSteps->setValue(0.1);
                SaveFieldSteps->setToolTip("Time step to save fields while calculating");
                layout->addWidget(SaveFieldSteps, 1, 1);

                m_saveFieldStepsLabel = new QLabel("Field step");
                layout->addWidget(m_saveFieldStepsLabel, 1, 0);

                retranslateUi(widget);
            }
        };
    }
}
}

#endif

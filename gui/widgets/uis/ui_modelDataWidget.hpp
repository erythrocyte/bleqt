#ifndef BLE_GUI_WIDGETS_UI_MODELDATA_H_
#define BLE_GUI_WIDGETS_UI_MODELDATA_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace ble::gui::widgets::UI {

class ModelData {

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

        SaveFieldSteps->setToolTip("Time step to save fields while calculating");
        Period->setToolTip("Calculation time period");
    }

    void setupUi(QWidget* widget)
    {
        int max_col = 10;
        m_groupBox = new QGroupBox("Modeling data");
        QVBoxLayout* mainLayout = new QVBoxLayout(widget);
        mainLayout->addWidget(m_groupBox);
        QGridLayout* layout = new QGridLayout(m_groupBox);
        m_groupBox->setLayout(layout);

        layout->setMargin(5);

        m_periodLabel = new QLabel("Period");
        Period = new QDoubleSpinBox();
        Period->setMinimum(0.1);
        Period->setMaximum(1e10);
        Period->setSingleStep(0.1);
        Period->setValue(5);
        Period->setToolTip("Calculation time period");
        layout->addWidget(m_periodLabel, 0, 0);
        layout->addWidget(Period, 0, 1, 1, max_col);

        m_saveFieldStepsLabel = new QLabel("Field step");
        SaveFieldSteps = new QDoubleSpinBox();
        SaveFieldSteps->setMinimum(0.01);
        SaveFieldSteps->setMaximum(5);
        SaveFieldSteps->setSingleStep(0.01);
        SaveFieldSteps->setValue(0.1);
        SaveFieldSteps->setToolTip("Time step to save fields while calculating");
        layout->addWidget(m_saveFieldStepsLabel, 1, 0);
        layout->addWidget(SaveFieldSteps, 1, 1, 1, max_col);

        retranslateUi(widget);
    }

private:
    QGroupBox* m_groupBox;
    QLabel* m_periodLabel;
    QLabel* m_saveFieldStepsLabel;
};

}

#endif

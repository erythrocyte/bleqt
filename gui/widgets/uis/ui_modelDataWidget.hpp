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
private:
    QGroupBox* m_groupBox;
    QLabel* m_periodLabel;
    QLabel* m_saveFieldStepsLabel;
    QLabel* m_boundSaturLabel;
    QLabel* m_initialSaturTypeLabel;
    QLabel* m_initialsSaturConstLabel;
    QLabel* m_initialSaturFileLabel;

public:
    QDoubleSpinBox* Period;
    QDoubleSpinBox* SaveFieldSteps;
    QDoubleSpinBox* BoundSatur;
    QDoubleSpinBox* InitialConstSatur;
    QPushButton* InitialSaturFileChooseButton;
    QComboBox* InitialSaturType;
    QLineEdit* InitialSaturFile;

    void retranslateUi(QWidget* widget)
    {
        m_groupBox->setTitle("Modeling data");
        m_groupBox->setToolTip("Modeling data");

        m_periodLabel->setText("Period");
        m_periodLabel->setToolTip("Period");

        m_saveFieldStepsLabel->setText("Field step");
        m_saveFieldStepsLabel->setToolTip("Field step");

        m_boundSaturLabel->setText("Bound satur");
        m_boundSaturLabel->setToolTip("Bound satur");

        m_initialSaturTypeLabel->setText("Init satur type");
        m_initialSaturTypeLabel->setToolTip("Init satur type");

        m_initialsSaturConstLabel->setText("Init satur (const");
        m_initialsSaturConstLabel->setToolTip("Init satur (const");

        m_initialSaturFileLabel->setText("Init satur (file)");
        m_initialSaturFileLabel->setToolTip("Init satur (file)");

        InitialSaturFileChooseButton->setText("...");
        InitialSaturFileChooseButton->setToolTip("Choose file with initial saturation distribution");

        SaveFieldSteps->setToolTip("Time step to save fields while calculating");
        Period->setToolTip("Calculation time period");

        BoundSatur->setToolTip("Bound satur value");

        InitialConstSatur->setToolTip("Initial saturation value");
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

        m_boundSaturLabel = new QLabel("Bound satur");
        BoundSatur = new QDoubleSpinBox();
        BoundSatur->setMinimum(0.0);
        BoundSatur->setMaximum(1.0);
        BoundSatur->setSingleStep(0.01);
        BoundSatur->setValue(1.0);
        BoundSatur->setToolTip("Bound satur value");
        layout->addWidget(m_boundSaturLabel, 2, 0);
        layout->addWidget(BoundSatur, 2, 1, 1, max_col);

        m_initialSaturTypeLabel = new QLabel("Init satur type");
        InitialSaturType = new QComboBox(widget);
        layout->addWidget(m_initialSaturTypeLabel, 3, 0);
        layout->addWidget(InitialSaturType, 3, 1, 1, max_col);

        m_initialsSaturConstLabel = new QLabel("Init satur type");
        InitialConstSatur = new QDoubleSpinBox();
        InitialConstSatur->setMinimum(0.0);
        InitialConstSatur->setMaximum(1.0);
        InitialConstSatur->setSingleStep(0.01);
        InitialConstSatur->setValue(0.0);
        InitialConstSatur->setToolTip("Initial saturation value");
        layout->addWidget(m_initialsSaturConstLabel, 4, 0);
        layout->addWidget(InitialConstSatur, 4, 1, 1, max_col);

        m_initialSaturFileLabel = new QLabel("Init satur type");
        InitialSaturFile = new QLineEdit();
        InitialSaturFile->setReadOnly(true);
        InitialSaturFile->setEnabled(false);
        InitialSaturFileChooseButton = new QPushButton();
        InitialSaturFileChooseButton->setText("...");
        InitialSaturFileChooseButton->setToolTip("Choose file with initial saturation distribution");
        InitialSaturFileChooseButton->setStyleSheet("padding: 0px 5px 0px 5px;");
        InitialSaturFileChooseButton->setEnabled(false);
        layout->addWidget(m_initialSaturFileLabel, 5, 0);
        layout->addWidget(InitialSaturFile, 5, 1, 1, 9);
        layout->addWidget(InitialSaturFileChooseButton, 5, max_col, 1, 1);

        retranslateUi(widget);
    }
};

}

#endif

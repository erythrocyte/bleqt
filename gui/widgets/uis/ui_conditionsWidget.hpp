#ifndef BLE_GUI_WIDGETS_UI_CONDITIONSWIDGET_H_
#define BLE_GUI_WIDGETS_UI_CONDITIONSWIDGET_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

namespace ble::gui::widgets::UI {

class Conditions {

public:
    QComboBox* ContourBoundType;
    QComboBox* TopBotCondType;
    QLineEdit* BoundUFile;
    QPushButton* BoundUFileChooseButton;
    QDoubleSpinBox* BoundUConstValue;
    QSpinBox* TopBotBoundConstLenght;
    QDoubleSpinBox* BoundSatur;
    QDoubleSpinBox* InitialConstSatur;
    QPushButton* InitialSaturFileChooseButton;
    QComboBox* InitialSaturType;
    QLineEdit* InitialSaturFile;

    void retranslateUi(QWidget* widget)
    {
        groupBox->setTitle("Boundary Conditions");
        groupBox->setToolTip("Boundary Conditions");

        m_contourBoundTypeLabel->setText("CB Type");
        m_contourBoundTypeLabel->setToolTip("Contour Bound Type");

        m_rhsTypeLabel->setText("RHS Type");
        m_rhsTypeLabel->setToolTip("RHS Type");

        m_boundUFileLabel->setText("RHS File");
        m_boundUFileLabel->setToolTip("RHS File");

        m_boundUConstValueLabel->setText("U value");
        m_boundUConstValueLabel->setToolTip("Top and Bottom faces u value");

        m_boundConstLenghtLabel->setText("Const bound len");
        m_boundConstLenghtLabel->setToolTip("Top and Bottom faces bound const value lenght in \% from right bound");

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

        BoundSatur->setToolTip("Bound satur value");

        InitialConstSatur->setToolTip("Initial saturation value");
    }

    void setupUI(QWidget* widget)
    {
        int max_col = 10;
        groupBox = new QGroupBox("Boundary Conditions");
        mainLayout = new QVBoxLayout(widget);
        mainLayout->addWidget(groupBox);
        layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

        ContourBoundType = new QComboBox();
        m_contourBoundTypeLabel = new QLabel("CB Type");
        layout->addWidget(m_contourBoundTypeLabel, 0, 0, 1, 1);
        layout->addWidget(ContourBoundType, 0, 1, 1, max_col);

        TopBotCondType = new QComboBox();
        TopBotCondType->setEnabled(false);
        m_rhsTypeLabel = new QLabel("RHS Type");
        layout->addWidget(m_rhsTypeLabel, 1, 0, 1, 1);
        layout->addWidget(TopBotCondType, 1, 1, 1, max_col);

        m_boundUFileLabel = new QLabel("RHS File");
        BoundUFile = new QLineEdit();
        BoundUFile->setEnabled(false);
        BoundUFile->setReadOnly(true);
        BoundUFileChooseButton = new QPushButton("...");
        BoundUFileChooseButton->setEnabled(false);
        BoundUFileChooseButton->setStyleSheet("padding: 0px 5px 0px 5px;");
        layout->addWidget(m_boundUFileLabel, 2, 0, 1, 1);
        layout->addWidget(BoundUFile, 2, 1, 1, 9);
        layout->addWidget(BoundUFileChooseButton, 2, max_col, 1, 1);

        BoundUConstValue = new QDoubleSpinBox();
        BoundUConstValue->setMinimum(-10.0);
        BoundUConstValue->setMaximum(10);
        BoundUConstValue->setSingleStep(1e-3);
        BoundUConstValue->setValue(0.01);
        BoundUConstValue->setDecimals(3);
        BoundUConstValue->setEnabled(false);
        m_boundUConstValueLabel = new QLabel("Const value");
        layout->addWidget(m_boundUConstValueLabel, 3, 0, 1, 1);
        layout->addWidget(BoundUConstValue, 3, 1, 1, 10);

        TopBotBoundConstLenght = new QSpinBox();
        TopBotBoundConstLenght->setMinimum(0);
        TopBotBoundConstLenght->setMaximum(100);
        TopBotBoundConstLenght->setSingleStep(1);
        TopBotBoundConstLenght->setValue(100);
        TopBotBoundConstLenght->setEnabled(false);
        m_boundConstLenghtLabel = new QLabel("Const lenght");
        layout->addWidget(m_boundConstLenghtLabel, 4, 0, 1, 1);
        layout->addWidget(TopBotBoundConstLenght, 4, 1, 1, 10);

        m_boundSaturLabel = new QLabel("Bound satur");
        BoundSatur = new QDoubleSpinBox();
        BoundSatur->setMinimum(0.0);
        BoundSatur->setMaximum(1.0);
        BoundSatur->setSingleStep(0.01);
        BoundSatur->setValue(1.0);
        BoundSatur->setToolTip("Bound satur value");
        layout->addWidget(m_boundSaturLabel, 5, 0);
        layout->addWidget(BoundSatur, 5, 1, 1, max_col);

        m_initialSaturTypeLabel = new QLabel("Init satur type");
        InitialSaturType = new QComboBox(widget);
        layout->addWidget(m_initialSaturTypeLabel, 6, 0);
        layout->addWidget(InitialSaturType, 6, 1, 1, max_col);

        m_initialsSaturConstLabel = new QLabel("Init satur type");
        InitialConstSatur = new QDoubleSpinBox();
        InitialConstSatur->setMinimum(0.0);
        InitialConstSatur->setMaximum(1.0);
        InitialConstSatur->setSingleStep(0.01);
        InitialConstSatur->setValue(0.0);
        InitialConstSatur->setToolTip("Initial saturation value");
        layout->addWidget(m_initialsSaturConstLabel, 7, 0);
        layout->addWidget(InitialConstSatur, 7, 1, 1, max_col);

        m_initialSaturFileLabel = new QLabel("Init satur type");
        InitialSaturFile = new QLineEdit();
        InitialSaturFile->setReadOnly(true);
        InitialSaturFile->setEnabled(false);
        InitialSaturFileChooseButton = new QPushButton();
        InitialSaturFileChooseButton->setText("...");
        InitialSaturFileChooseButton->setToolTip("Choose file with initial saturation distribution");
        InitialSaturFileChooseButton->setStyleSheet("padding: 0px 5px 0px 5px;");
        InitialSaturFileChooseButton->setEnabled(false);
        layout->addWidget(m_initialSaturFileLabel, 8, 0);
        layout->addWidget(InitialSaturFile, 8, 1, 1, 9);
        layout->addWidget(InitialSaturFileChooseButton, 8, max_col, 1, 1);

        retranslateUi(widget);
    }

private:
    QGroupBox* groupBox;
    QVBoxLayout* mainLayout;
    QGridLayout* layout;
    QLabel* m_contourBoundTypeLabel;
    QLabel* m_rhsTypeLabel;
    QLabel* m_boundUFileLabel;
    QLabel* m_boundUConstValueLabel;
    QLabel* m_boundConstLenghtLabel;
    QLabel* m_boundSaturLabel;
    QLabel* m_initialSaturTypeLabel;
    QLabel* m_initialsSaturConstLabel;
    QLabel* m_initialSaturFileLabel;
};

}

#endif
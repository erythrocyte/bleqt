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
    QComboBox* RHSType;
    QLineEdit* RHSFile;
    QPushButton* RHSFileChooseButton;
    QDoubleSpinBox* RHSConstValue;
    QSpinBox* RHSConstLenght;

    void retranslateUi(QWidget* widget)
    {
        groupBox->setTitle("Boundary Conditions");
        groupBox->setToolTip("Boundary Conditions");

        m_contourBoundTypeLabel->setText("CB Type");
        m_contourBoundTypeLabel->setToolTip("Contour Bound Type");

        m_RHSTypeLabel->setText("RHS Type");
        m_RHSTypeLabel->setToolTip("RHS Type");

        m_RHSFileLabel->setText("RHS File");
        m_RHSFileLabel->setToolTip("RHS File");

        m_RHSConstValueLabel->setText("Const value");
        m_RHSConstValueLabel->setToolTip("Const value");

        m_RHSConstLenghtLabel->setText("Const value");
        m_RHSConstLenghtLabel->setToolTip("Const value lenght in \% from right bound");
    }

    void setupUI(QWidget* widget)
    {
        groupBox = new QGroupBox("Boundary Conditions");
        mainLayout = new QVBoxLayout(widget);
        mainLayout->addWidget(groupBox);
        layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

        ContourBoundType = new QComboBox();
        m_contourBoundTypeLabel = new QLabel("CB Type");
        layout->addWidget(m_contourBoundTypeLabel, 0, 0, 1, 1);
        layout->addWidget(ContourBoundType, 0, 1, 1, 10);

        RHSType = new QComboBox();
        RHSType->setEnabled(false);
        m_RHSTypeLabel = new QLabel("RHS Type");
        layout->addWidget(m_RHSTypeLabel, 1, 0, 1, 1);
        layout->addWidget(RHSType, 1, 1, 1, 10);

        m_RHSFileLabel = new QLabel("RHS File");
        RHSFile = new QLineEdit();
        RHSFile->setEnabled(false);
        RHSFile->setReadOnly(true);
        RHSFileChooseButton = new QPushButton("...");
        RHSFileChooseButton->setEnabled(false);
        RHSFileChooseButton->setStyleSheet("padding: 0px 5px 0px 5px;");
        layout->addWidget(m_RHSFileLabel, 2, 0, 1, 1);
        layout->addWidget(RHSFile, 2, 1, 1, 9);
        layout->addWidget(RHSFileChooseButton, 2, 10, 1, 1);

        RHSConstValue = new QDoubleSpinBox();
        RHSConstValue->setMinimum(-10.0);
        RHSConstValue->setMaximum(10);
        RHSConstValue->setSingleStep(1e-3);
        RHSConstValue->setValue(0.01);
        RHSConstValue->setDecimals(3);
        RHSConstValue->setEnabled(false);
        m_RHSConstValueLabel = new QLabel("Const value");
        layout->addWidget(m_RHSConstValueLabel, 3, 0, 1, 1);
        layout->addWidget(RHSConstValue, 3, 1, 1, 10);

        RHSConstLenght = new QSpinBox();
        RHSConstLenght->setMinimum(0);
        RHSConstLenght->setMaximum(100);
        RHSConstLenght->setSingleStep(1);
        RHSConstLenght->setValue(100);
        RHSConstLenght->setEnabled(false);
        m_RHSConstLenghtLabel = new QLabel("Const lenght");
        layout->addWidget(m_RHSConstLenghtLabel, 4, 0, 1, 1);
        layout->addWidget(RHSConstLenght, 4, 1, 1, 10);

        retranslateUi(widget);
    }

private:
    QGroupBox* groupBox;
    QVBoxLayout* mainLayout;
    QGridLayout* layout;
    QLabel* m_contourBoundTypeLabel;
    QLabel* m_RHSTypeLabel;
    QLabel* m_RHSFileLabel;
    QLabel* m_RHSConstValueLabel;
    QLabel* m_RHSConstLenghtLabel;
};

}

#endif
#ifndef BLE_GUI_WIDGETS_UI_BOUNDARYCONDITIONSWIDGET_H_
#define BLE_GUI_WIDGETS_UI_BOUNDARYCONDITIONSWIDGET_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

namespace ble::gui::widgets::UI {

class BoundaryConditions {

public:
    QComboBox* ContourBondType;
    QComboBox* RHSType;
    QTextEdit* RHSFile;
    QPushButton* RHSFileChooseButton;

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
    }

    void setupUI(QWidget* widget)
    {
        groupBox = new QGroupBox("Boundary Conditions");
        mainLayout = new QVBoxLayout(widget);
        mainLayout->addWidget(groupBox);
        layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

        ContourBondType = new QComboBox();
        m_contourBoundTypeLabel = new QLabel("CB Type");
        layout->addWidget(m_contourBoundTypeLabel, 0, 0, 1, 1);
        layout->addWidget(ContourBondType, 0, 1, 1, 5);
        
        RHSType = new QComboBox();        
        m_RHSTypeLabel = new QLabel("RHS Type");
        // layout->addWidget(m_RHSTypeLabel, 1, 0, 1 ,1);
        // layout->addWidget(RHSType, 1, 1, 2, 5);

        m_RHSFileLabel = new QLabel("RHS File");
        RHSFile = new QTextEdit();
        RHSFileChooseButton = new QPushButton();
        // layout->addWidget(RHSFile, 2, 1, 2, 4);        
        // layout->addWidget(m_RHSFileLabel, 2, 0, 1, 1);
        // layout->addWidget(RHSFileChooseButton, 2, 5, 1, 1);

        retranslateUi(widget);
    }

private:
    QGroupBox* groupBox;
    QVBoxLayout* mainLayout;
    QGridLayout* layout;
    QLabel* m_contourBoundTypeLabel;
    QLabel* m_RHSTypeLabel;
    QLabel* m_RHSFileLabel;
};

}

#endif
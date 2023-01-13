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
#include <QScrollArea>
#include <QSpinBox>
#include <QWidget>

#include "widgets/fractShoreBoundaryWidget.hpp"

namespace ble::gui::widgets::UI {

class Conditions {

public:
    QComboBox* ContourBoundType;
    QSpinBox* TopBotBoundConstLenght;
    QDoubleSpinBox* BoundSatur;
    QComboBox* BoundSType;
    QLineEdit* BoundSFile;
    QPushButton* BoundSFileChooseButton;
    QDoubleSpinBox* BoundSConstValue;
    QDoubleSpinBox* PressureContour;
    QDoubleSpinBox* PressureWell;

    // initial
    QDoubleSpinBox* init_satur;
    QPushButton* init_satur_file_button;
    QComboBox* init_satur_type;
    QLineEdit* init_satur_file;

    // fract end;
    QCheckBox* fract_end_imperm;
    QDoubleSpinBox* press_fract_end;
    QDoubleSpinBox* sat_fract_end;

    // well
    QDoubleSpinBox* p_well;
    QDoubleSpinBox* s_well;

    widgets::FractShoreWidget* fract_shores_left_right;

    void setupUI(QWidget* widget)
    {
        setupUiBound(widget);
        setupUiInit(widget);

        auto gb = new QGroupBox();
        auto gl = new QGridLayout(gb);
        gb->setLayout(gl);
        gl->setMargin(5);

        auto vbl = new QVBoxLayout(widget);

        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidget(gb);
        scrollArea->setWidgetResizable(true);
        vbl->addWidget(scrollArea);

        m_layout = new QGridLayout(widget);
        // widget->setLayout(m_layout);

        gl->addWidget(m_gbInit, 0, 0, 1, 1);
        gl->addWidget(m_gbBound, 1, 0, 1, 1);
    }

private:
    QGroupBox* m_gbBound;
    QGroupBox* m_gbInit;
    QGridLayout* m_layout;
    QGroupBox* m_gb_fract_end;
    QGroupBox* m_gb_well;

    QLabel* m_contourBoundTypeLabel;
    QLabel* m_boundConstLenghtLabel;
    QLabel* m_boundSaturLabel;
    QLabel* m_boundSTypeLabel;
    QLabel* m_boundSFileLabel;
    QLabel* m_boundSConstValueLabel;
    QLabel* m_pressureContour;
    QLabel* m_pressureWell;

    // initial
    QLabel* m_initialSaturTypeLabel;
    QLabel* m_initialsSaturConstLabel;
    QLabel* m_initialSaturFileLabel;

    // fract end;
    QLabel* m_s_fract_end_label;
    QLabel* m_p_fract_end_label;

    // well
    QLabel* m_s_well_label;
    QLabel* m_p_well_label;

    void setupUiBound(QWidget* widget)
    {
        // int max_col = 10;
        m_gbBound = new QGroupBox("Boundary");
        auto layout = new QGridLayout();
        m_gbBound->setLayout(layout);
        layout->setMargin(5);

        prepareGbFractEnd();
        prepareGbWell();
        fract_shores_left_right = new widgets::FractShoreWidget(widget);

        layout->addWidget(m_gb_fract_end, 0, 0);
        layout->addWidget(m_gb_well, 1, 0);
        layout->addWidget(fract_shores_left_right, 2, 0);

        ContourBoundType = new QComboBox();
        m_contourBoundTypeLabel = new QLabel("CB Type");
        // layout->addWidget(m_contourBoundTypeLabel, 0, 0, 1, 1);
        // layout->addWidget(ContourBoundType, 0, 1, 1, max_col);

        m_boundConstLenghtLabel = new QLabel("Lenght");
        TopBotBoundConstLenght = new QSpinBox();
        TopBotBoundConstLenght->setMinimum(0);
        TopBotBoundConstLenght->setMaximum(100);
        TopBotBoundConstLenght->setSingleStep(1);
        TopBotBoundConstLenght->setValue(20);
        // layout->addWidget(m_boundConstLenghtLabel, 1, 0, 1, 1);
        // layout->addWidget(TopBotBoundConstLenght, 1, 1, 1, 10);

        m_boundSaturLabel = new QLabel("Satur on bound");
        BoundSatur = new QDoubleSpinBox();
        BoundSatur->setMinimum(0.0);
        BoundSatur->setMaximum(1.0);
        BoundSatur->setSingleStep(0.01);
        BoundSatur->setValue(1.0);
        BoundSatur->setDecimals(3);
        BoundSatur->setToolTip("Bound satur value");
        // layout->addWidget(m_boundSaturLabel, 2, 0);
        // layout->addWidget(BoundSatur, 2, 1, 1, max_col);

        m_boundSTypeLabel = new QLabel("Bound S Type");
        BoundSType = new QComboBox();
        BoundSType->setEnabled(false);
        // layout->addWidget(m_boundSTypeLabel, 3, 0, 1, 1);
        // layout->addWidget(BoundSType, 3, 1, 1, max_col);

        m_boundSFileLabel = new QLabel("S value");
        BoundSFile = new QLineEdit();
        BoundSFile->setEnabled(false);
        BoundSFile->setReadOnly(true);
        BoundSFileChooseButton = new QPushButton("...");
        BoundSFileChooseButton->setEnabled(false);
        BoundSFileChooseButton->setStyleSheet("padding: 0px 5px 0px 5px;");
        // layout->addWidget(m_boundSFileLabel, 4, 0, 1, 1);
        // layout->addWidget(BoundSFile, 4, 1, 1, 9);
        // layout->addWidget(BoundSFileChooseButton, 4, max_col, 1, 1);

        m_boundSConstValueLabel = new QLabel("S value");
        BoundSConstValue = new QDoubleSpinBox();
        BoundSConstValue->setMinimum(0.0);
        BoundSConstValue->setMaximum(1.0);
        BoundSConstValue->setSingleStep(1e-3);
        BoundSConstValue->setValue(0.01);
        BoundSConstValue->setDecimals(3);
        BoundSConstValue->setEnabled(false);
        // layout->addWidget(m_boundSConstValueLabel, 5, 0, 1, 1);
        // layout->addWidget(BoundSConstValue, 5, 1, 1, max_col);

        m_pressureContour = new QLabel("Pc, at");
        PressureContour = new QDoubleSpinBox();
        PressureContour->setMinimum(0.0);
        PressureContour->setMaximum(1000);
        PressureContour->setSingleStep(10);
        PressureContour->setValue(150);
        PressureContour->setToolTip("Contour pressure value");
        // layout->addWidget(m_pressureContour, 6, 0);
        // layout->addWidget(PressureContour, 6, 1, 1, max_col);

        m_pressureWell = new QLabel("Pw, at");
        PressureWell = new QDoubleSpinBox();
        PressureWell->setMinimum(0.0);
        PressureWell->setMaximum(1000);
        PressureWell->setSingleStep(10);
        PressureWell->setValue(100);
        PressureWell->setToolTip("Well pressure value");
        // layout->addWidget(m_pressureWell, 7, 0);
        // layout->addWidget(PressureWell, 7, 1, 1, max_col);

        // retranslateUiBound(widget);
    }

    void retranslateUiBound(QWidget* widget)
    {
        m_gbBound->setTitle("Boundary");
        m_gbBound->setToolTip("Boundary Conditions");
        m_contourBoundTypeLabel->setText("CB Type");
        m_contourBoundTypeLabel->setToolTip("Contour Bound Type");
        m_boundSTypeLabel->setText("Bound S Type");
        m_boundSTypeLabel->setToolTip("Top and Bottom faces bound s type");
        m_boundSFileLabel->setText("S File");
        m_boundSFileLabel->setToolTip("Bound S File");
        m_boundSConstValueLabel->setText("S value");
        m_boundSConstValueLabel->setToolTip("Top and Bottom faces saturation value");
        m_boundConstLenghtLabel->setText("Const bound len");
        m_boundConstLenghtLabel->setToolTip("Top and Bottom faces bound const value lenght in \% from right bound");
        m_boundSaturLabel->setText("Bound satur");
        m_boundSaturLabel->setToolTip("Bound satur");
        BoundSatur->setToolTip("Bound satur value");
    }

    void prepareGbFractEnd()
    {
        m_gb_fract_end = new QGroupBox("Fract end");
        auto layout = new QGridLayout();
        m_gb_fract_end->setLayout(layout);

        fract_end_imperm = new QCheckBox("Impermeable");
        fract_end_imperm->setChecked(false);
        layout->addWidget(fract_end_imperm, 0, 0, 1, 3);

        m_p_fract_end_label = new QLabel("p, at");
        press_fract_end = new QDoubleSpinBox();
        press_fract_end->setMinimum(-1e8);
        press_fract_end->setMaximum(1e8);
        press_fract_end->setValue(150);
        layout->addWidget(m_p_fract_end_label, 1, 0, 1, 1);
        layout->addWidget(press_fract_end, 1, 1, 1, 2);

        m_s_fract_end_label = new QLabel("s");
        sat_fract_end = new QDoubleSpinBox();
        sat_fract_end->setMinimum(0.0);
        sat_fract_end->setMaximum(1.0);
        sat_fract_end->setValue(1.0);
        sat_fract_end->setSingleStep(0.1);
        layout->addWidget(m_s_fract_end_label, 2, 0, 1, 1);
        layout->addWidget(sat_fract_end, 2, 1, 1, 2);
    }

    void prepareGbWell()
    {
        m_gb_well = new QGroupBox("Well");
        auto layout = new QGridLayout();
        m_gb_well->setLayout(layout);

        m_p_well_label = new QLabel("p, at");
        p_well = new QDoubleSpinBox();
        p_well->setMinimum(-1e8);
        p_well->setMaximum(1e8);
        p_well->setValue(100);
        layout->addWidget(m_p_well_label, 0, 0, 1, 1);
        layout->addWidget(p_well, 0, 1, 1, 2);

        m_s_well_label = new QLabel("s");
        s_well = new QDoubleSpinBox();
        s_well->setMinimum(0.0);
        s_well->setMaximum(1.0);
        s_well->setValue(1.0);
        s_well->setSingleStep(0.1);
        s_well->setEnabled(false);
        layout->addWidget(m_s_well_label, 1, 0, 1, 1);
        layout->addWidget(s_well, 1, 1, 1, 2);
    }

    void setupUiInit(QWidget* widget)
    {
        int max_col = 10;
        m_gbInit = new QGroupBox("Initial");
        auto layout = new QGridLayout();
        m_gbInit->setLayout(layout);

        m_initialSaturTypeLabel = new QLabel("Init satur type");
        init_satur_type = new QComboBox(widget);
        layout->addWidget(m_initialSaturTypeLabel, 0, 0);
        layout->addWidget(init_satur_type, 0, 1, 1, max_col);

        m_initialsSaturConstLabel = new QLabel("Init satur type");
        init_satur = new QDoubleSpinBox();
        init_satur->setMinimum(0.0);
        init_satur->setMaximum(1.0);
        init_satur->setSingleStep(0.01);
        init_satur->setValue(0.0);
        init_satur->setToolTip("Initial saturation value");
        layout->addWidget(m_initialsSaturConstLabel, 1, 0);
        layout->addWidget(init_satur, 1, 1, 1, max_col);

        m_initialSaturFileLabel = new QLabel("Init satur type");
        init_satur_file = new QLineEdit();
        init_satur_file->setReadOnly(true);
        init_satur_file->setEnabled(false);
        init_satur_file_button = new QPushButton();
        init_satur_file_button->setText("...");
        init_satur_file_button->setToolTip("Choose file with initial saturation distribution");
        init_satur_file_button->setStyleSheet("padding: 0px 5px 0px 5px;");
        init_satur_file_button->setEnabled(false);
        layout->addWidget(m_initialSaturFileLabel, 2, 0);
        layout->addWidget(init_satur_file, 2, 1, 1, 9);
        layout->addWidget(init_satur_file_button, 2, max_col, 1, 1);

        retranslateUiInit(widget);
    }

    void retranslateUiInit(QWidget* widget)
    {
        m_gbInit->setTitle("Initial");
        m_gbInit->setToolTip("Initial Conditions");
        m_initialSaturTypeLabel->setText("Satur type");
        m_initialSaturTypeLabel->setToolTip("Initail saturation type");
        m_initialsSaturConstLabel->setText("Satur (const)");
        m_initialsSaturConstLabel->setToolTip("Initial constant saturation value");
        m_initialSaturFileLabel->setText("Satur (file)");
        m_initialSaturFileLabel->setToolTip("Initial saturation distribution file");
        init_satur_file_button->setText("...");
        init_satur_file_button->setToolTip("Choose file with initial saturation distribution");
        init_satur->setToolTip("Initial saturation value");
    }
};

}

#endif
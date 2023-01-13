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
    // initial
    QGroupBox* gb_init;
    QDoubleSpinBox* init_satur;
    QPushButton* init_satur_file_button;
    QComboBox* init_satur_type;
    QLineEdit* init_satur_file;
    QLabel* init_satur_label;
    QLabel* init_satur_file_label;

    // fract end;
    QCheckBox* fract_end_imperm;
    QDoubleSpinBox* press_fract_end;
    QDoubleSpinBox* sat_fract_end;
    QLabel* s_fract_end_label;
    QLabel* p_fract_end_label;

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

        auto vbl = new QVBoxLayout();

        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidget(gb);
        scrollArea->setWidgetResizable(true);
        vbl->addWidget(scrollArea);

        widget->setLayout(vbl);

        gl->addWidget(gb_init, 0, 0, 1, 1);
        gl->addWidget(m_gb_bound, 1, 0, 1, 1);
    }

private:
    QGroupBox* m_gb_bound;
    QGridLayout* m_layout;
    QGroupBox* m_gb_fract_end;
    QGroupBox* m_gb_well;

    // initial
    QLabel* m_init_satur_type_label;

    // well
    QLabel* m_s_well_label;
    QLabel* m_p_well_label;

    void setupUiBound(QWidget* widget)
    {
        // int max_col = 10;
        m_gb_bound = new QGroupBox("Boundary");
        auto layout = new QGridLayout();
        m_gb_bound->setLayout(layout);
        layout->setMargin(5);

        prepareGbFractEnd();
        prepareGbWell();
        fract_shores_left_right = new widgets::FractShoreWidget(widget);

        layout->addWidget(m_gb_fract_end, 0, 0);
        layout->addWidget(m_gb_well, 1, 0);
        layout->addWidget(fract_shores_left_right, 2, 0);

        // retranslateUiBound(widget);
    }

    void retranslateUiBound(QWidget* widget)
    {
        m_gb_bound->setTitle("Boundary");
        m_gb_bound->setToolTip("Boundary Conditions");
    }

    void prepareGbFractEnd()
    {
        m_gb_fract_end = new QGroupBox("Fract end");
        auto layout = new QGridLayout();
        m_gb_fract_end->setLayout(layout);

        fract_end_imperm = new QCheckBox("Impermeable");
        fract_end_imperm->setChecked(true);
        layout->addWidget(fract_end_imperm, 0, 0, 1, 3);

        p_fract_end_label = new QLabel("p, at");
        p_fract_end_label->setEnabled(false);
        press_fract_end = new QDoubleSpinBox();
        press_fract_end->setMinimum(-1e8);
        press_fract_end->setMaximum(1e8);
        press_fract_end->setValue(150);
        press_fract_end->setEnabled(false);
        layout->addWidget(p_fract_end_label, 1, 0, 1, 1);
        layout->addWidget(press_fract_end, 1, 1, 1, 2);

        s_fract_end_label = new QLabel("s");
        s_fract_end_label->setEnabled(false);
        sat_fract_end = new QDoubleSpinBox();
        sat_fract_end->setMinimum(0.0);
        sat_fract_end->setMaximum(1.0);
        sat_fract_end->setValue(1.0);
        sat_fract_end->setSingleStep(0.1);
        sat_fract_end->setEnabled(false);
        layout->addWidget(s_fract_end_label, 2, 0, 1, 1);
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
        gb_init = new QGroupBox("Initial");
        auto layout = new QGridLayout();
        gb_init->setLayout(layout);

        m_init_satur_type_label = new QLabel("Init satur type");
        init_satur_type = new QComboBox(widget);
        layout->addWidget(m_init_satur_type_label, 0, 0);
        layout->addWidget(init_satur_type, 0, 1, 1, max_col);

        init_satur_label = new QLabel("Init satur type");
        init_satur = new QDoubleSpinBox();
        init_satur->setMinimum(0.0);
        init_satur->setMaximum(1.0);
        init_satur->setSingleStep(0.01);
        init_satur->setValue(0.0);
        init_satur->setToolTip("Initial saturation value");
        layout->addWidget(init_satur_label, 1, 0);
        layout->addWidget(init_satur, 1, 1, 1, max_col);

        init_satur_file_label = new QLabel("Init satur type");
        init_satur_file_label->setEnabled(false);
        init_satur_file = new QLineEdit();
        init_satur_file->setReadOnly(true);
        init_satur_file->setEnabled(false);
        init_satur_file_button = new QPushButton();
        init_satur_file_button->setText("...");
        init_satur_file_button->setToolTip("Choose file with initial saturation distribution");
        init_satur_file_button->setStyleSheet("padding: 0px 5px 0px 5px;");
        init_satur_file_button->setEnabled(false);
        layout->addWidget(init_satur_file_label, 2, 0);
        layout->addWidget(init_satur_file, 2, 1, 1, 9);
        layout->addWidget(init_satur_file_button, 2, max_col, 1, 1);

        retranslateUiInit(widget);
    }

    void retranslateUiInit(QWidget* widget)
    {
        gb_init->setTitle("Initial");
        gb_init->setToolTip("Initial Conditions");
        m_init_satur_type_label->setText("Type");
        m_init_satur_type_label->setToolTip("Initail saturation type");
        init_satur_label->setText("S");
        init_satur_label->setToolTip("Initial constant saturation value");
        init_satur_file_label->setText("File");
        init_satur_file_label->setToolTip("Initial saturation distribution file");
        init_satur_file_button->setText("...");
        init_satur_file_button->setToolTip("Choose file with initial saturation distribution");
        init_satur->setToolTip("Initial saturation value");
    }
};

}

#endif
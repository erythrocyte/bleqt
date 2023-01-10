#ifndef BLE_GUI_WIDGETS_UI_DATAWIDGET_H_
#define BLE_GUI_WIDGETS_UI_DATAWIDGET_H_

#include <iostream>

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {

class Data {

public:
    // QVBoxLayout* MainLayout;

    // geology
    QDoubleSpinBox* Perm;
    QDoubleSpinBox* PermFract;
    QDoubleSpinBox* PoroFract;

    // geom
    QDoubleSpinBox* R;
    QDoubleSpinBox* L;
    QDoubleSpinBox* Delta;
    QDoubleSpinBox* Rw;

    // model data
    QDoubleSpinBox* Period;
    QDoubleSpinBox* FwLimit;
    QCheckBox* UseFwLimit;

    // relative permeability
    QDoubleSpinBox* MuWat;
    QDoubleSpinBox* MuOil;
    QSpinBox* N;

    void setupUI(QWidget* widget)
    {
        setupUiGeology(widget);
        setupUiGeom(widget);
        setupUiModelData(widget);
        setupUiRelPerm(widget);
        setupUiMain(widget);
    }

private:
    // QWidget* m_window;
    // QScrollArea* m_scrollArea;
    QVBoxLayout* m_layout;

    // geology
    QGroupBox* m_gbGeology;
    QGridLayout* m_layoutGeology;
    QLabel* m_labelPerm;
    QLabel* m_labelPoroFract;
    QLabel* m_labelPermFract;

    // geom
    QGridLayout* m_layoutGeom;
    QLabel* m_labelR;
    QLabel* m_labelL;
    QLabel* m_labelDelta;
    QLabel* m_labelRw;
    QGroupBox* m_gbGeom;

    // model data
    QGroupBox* m_gbModelData;
    QLabel* m_periodLabel;
    QLabel* m_saveFieldStepsLabel;

    // relative permeability
    QLabel* m_labelMuWat;
    QLabel* m_labelMuOil;
    QLabel* m_labelN;
    QGroupBox* m_gbRelPerm;

    void setupUiMain(QWidget* widget)
    {
        m_layout = new QVBoxLayout(widget);
        m_layout->addStretch();
        m_layout->setDirection(QVBoxLayout::BottomToTop);
        // MainLayout->setMargin(0);
        // MainLayout->setSpacing(0);
        // MainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        // MainLayout->addStretch();

        // m_window = new QWidget(widget);
        // m_window->setLayout(MainLayout);

        // m_scrollArea = new QScrollArea(widget);
        // m_scrollArea->setWidget(m_window);
        // m_scrollArea->setMinimumWidth(100);
        // m_scrollArea->setWidgetResizable(false);
        // m_scrollArea->show();

        // m_layout = new QVBoxLayout(widget);
        // m_layout->addWidget(m_scrollArea);

        widget->setLayout(m_layout);

        m_layout->addWidget(m_gbModelData);
        m_layout->addWidget(m_gbRelPerm);
        m_layout->addWidget(m_gbGeology);
        m_layout->addWidget(m_gbGeom);
    }

    void setupUiGeology(QWidget* widget)
    {
        m_gbGeology = new QGroupBox();
        m_layoutGeology = new QGridLayout(m_gbGeology);
        m_gbGeology->setLayout(m_layoutGeology);

        m_layoutGeology->setMargin(5);

        m_labelPerm = new QLabel("Permeability");
        Perm = new QDoubleSpinBox();
        Perm->setDecimals(2);
        Perm->setMinimum(1e-8);
        Perm->setMaximum(1e8);
        Perm->setSingleStep(1);
        Perm->setValue(0.01);
        m_layoutGeology->addWidget(m_labelPerm, 0, 0);
        m_layoutGeology->addWidget(Perm, 0, 1);

        m_labelPermFract = new QLabel("Perm fract");
        PermFract = new QDoubleSpinBox();
        PermFract->setDecimals(2);
        PermFract->setMinimum(1e-8);
        PermFract->setMaximum(1e8);
        PermFract->setSingleStep(1);
        PermFract->setValue(1);
        m_layoutGeology->addWidget(m_labelPermFract, 1, 0);
        m_layoutGeology->addWidget(PermFract, 1, 1);

        m_labelPoroFract = new QLabel("Porosity fract");
        PoroFract = new QDoubleSpinBox();
        PoroFract->setDecimals(1);
        PoroFract->setMinimum(0.1);
        PoroFract->setMaximum(0.7);
        PoroFract->setSingleStep(1e-1);
        PoroFract->setValue(0.2);
        m_layoutGeology->addWidget(m_labelPoroFract, 2, 0);
        m_layoutGeology->addWidget(PoroFract, 2, 1);

        retranslateUiGeology(widget);
    }

    void retranslateUiGeology(QWidget* widget)
    {
        m_gbGeology->setTitle("Geology");
        m_gbGeology->setToolTip("Geology data");

        m_labelPerm->setText("Res perm, d");
        m_labelPerm->setToolTip("Reservoir permeability, d");

        m_labelPermFract->setText("Fract perm, d");
        m_labelPermFract->setToolTip("Fracture  permeability, d");

        m_labelPoroFract->setText("Fract poro");
        m_labelPoroFract->setToolTip("Fracture porosity");
    }

    void setupUiGeom(QWidget* widget)
    {
        m_gbGeom = new QGroupBox();
        m_layoutGeom = new QGridLayout(m_gbGeom);
        m_gbGeom->setLayout(m_layoutGeom);
        m_layoutGeom->setMargin(5);

        m_labelR = new QLabel("R");
        R = new QDoubleSpinBox();
        R->setDecimals(1);
        R->setMinimum(1);
        R->setMaximum(1e6);
        R->setSingleStep(10);
        R->setValue(50);
        m_layoutGeom->addWidget(m_labelR, 0, 0);
        m_layoutGeom->addWidget(R, 0, 1);

        m_labelL = new QLabel("L");
        L = new QDoubleSpinBox();
        L->setDecimals(1);
        L->setMinimum(1);
        L->setMaximum(1e6);
        L->setSingleStep(10);
        L->setValue(100);
        m_layoutGeom->addWidget(m_labelL, 1, 0);
        m_layoutGeom->addWidget(L, 1, 1);

        m_labelDelta = new QLabel("Delta");
        Delta = new QDoubleSpinBox();
        Delta->setDecimals(3);
        Delta->setMinimum(1e-5);
        Delta->setMaximum(1);
        Delta->setSingleStep(1e-1);
        Delta->setValue(0.005);
        m_layoutGeom->addWidget(m_labelDelta, 2, 0);
        m_layoutGeom->addWidget(Delta, 2, 1);

        m_labelRw = new QLabel("Rw");
        Rw = new QDoubleSpinBox();
        Rw->setDecimals(2);
        Rw->setMinimum(0);
        Rw->setMaximum(1);
        Rw->setSingleStep(1e-2);
        Rw->setValue(0.1);
        m_layoutGeom->addWidget(m_labelRw, 3, 0);
        m_layoutGeom->addWidget(Rw, 3, 1);

        retranslateUiGeom(widget);
    }

    void retranslateUiGeom(QWidget* widget)
    {
        m_gbGeom->setTitle("Geometry");
        m_gbGeom->setToolTip("Geometry data");

        m_labelDelta->setText("Delta, m");
        m_labelDelta->setToolTip("Fracture half thickness, m");

        m_labelL->setText("L, m");
        m_labelL->setToolTip("Well half lenght, m");

        m_labelR->setText("R, m");
        m_labelR->setToolTip("Reservoir radius, m");

        m_labelRw->setText("Rw, m");
        m_labelRw->setToolTip("Well radius, m");
    }

    void setupUiModelData(QWidget* widget)
    {
        int max_col = 10;
        m_gbModelData = new QGroupBox("Modeling data");
        QGridLayout* layout = new QGridLayout(m_gbModelData);
        m_gbModelData->setLayout(layout);
        layout->setMargin(5);

        m_periodLabel = new QLabel("Period, h");
        Period = new QDoubleSpinBox();
        Period->setMinimum(0.1);
        Period->setMaximum(1e10);
        Period->setSingleStep(0.1);
        Period->setValue(5);
        Period->setToolTip("Calculation time period, hours");
        Period->setEnabled(false);
        layout->addWidget(m_periodLabel, 0, 0);
        layout->addWidget(Period, 0, 1, 1, max_col);

        m_saveFieldStepsLabel = new QLabel("Watercut limit, %");
        FwLimit = new QDoubleSpinBox();
        FwLimit->setMinimum(0.01);
        FwLimit->setMaximum(99);
        FwLimit->setSingleStep(1);
        FwLimit->setValue(98);
        FwLimit->setToolTip("Set modeling as a critical watercut value on well");
        layout->addWidget(m_saveFieldStepsLabel, 1, 0);
        layout->addWidget(FwLimit, 1, 1, 1, max_col);

        UseFwLimit = new QCheckBox("Use watercut limit");
        UseFwLimit->setCheckState(Qt::CheckState::Checked);
        layout->addWidget(UseFwLimit, 2, 0, 1, max_col);

        retranslateUiModelData(widget);
    }

    void retranslateUiModelData(QWidget* widget)
    {
        m_gbModelData->setTitle("Modeling data");
        m_gbModelData->setToolTip("Modeling data");

        m_periodLabel->setText("Period, h");
        m_periodLabel->setToolTip("Period in hours");

        m_saveFieldStepsLabel->setText("Watercut limit, %");
        m_saveFieldStepsLabel->setToolTip("Set modeling as a critical watercut value on well");

        FwLimit->setToolTip("Set modeling as a critical watercut value on well");
        Period->setToolTip("Calculation time period");

        UseFwLimit->setText("Use watercut limit");
        UseFwLimit->setToolTip("Use watercut limit if checked otherwise time limit will be used");
    }

    void setupUiRelPerm(QWidget* widget)
    {
        m_gbRelPerm = new QGroupBox();
        QGridLayout* layout = new QGridLayout(m_gbRelPerm);
        m_gbRelPerm->setLayout(layout);
        layout->setMargin(5);

        m_labelMuWat = new QLabel();
        MuWat = new QDoubleSpinBox();
        MuWat->setMinimum(1e-4);
        MuWat->setMaximum(1);
        MuWat->setSingleStep(0.1);
        MuWat->setDecimals(4);
        MuWat->setValue(1e-3);
        layout->addWidget(m_labelMuWat, 0, 0);
        layout->addWidget(MuWat, 0, 1);

        m_labelMuOil = new QLabel();
        MuOil = new QDoubleSpinBox();
        MuOil->setMinimum(1e-4);
        MuOil->setMaximum(1);
        MuOil->setSingleStep(0.1);
        MuOil->setDecimals(4);
        MuOil->setValue(1e-3);
        layout->addWidget(m_labelMuOil, 1, 0);
        layout->addWidget(MuOil, 1, 1);

        m_labelN = new QLabel();
        N = new QSpinBox();
        N->setMinimum(1);
        N->setMaximum(5);
        N->setValue(2);
        layout->addWidget(m_labelN, 2, 0);
        layout->addWidget(N, 2, 1);

        retranslateUiRelPerm(widget);
    }

    void retranslateUiRelPerm(QWidget* widget)
    {
        m_gbRelPerm->setTitle("Relative permeability data");
        m_gbRelPerm->setToolTip("Relative permeability data");

        m_labelMuWat->setText("Water visc, Pa*s");
        m_labelMuWat->setToolTip("Water viscosity, Pa*s");

        m_labelMuOil->setText("Oil visc, Pa*s");
        m_labelMuOil->setToolTip("Oil viscosity, Pa*s");

        m_labelN->setText("N");
        m_labelN->setToolTip("Relative permeability degree");
    }
};

}

#endif
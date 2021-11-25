#ifndef BLE_GUI_WIDGETS_UI_DATAWIDGET_H_
#define BLE_GUI_WIDGETS_UI_DATAWIDGET_H_

#include <iostream>

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QScrollArea>
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

    void setupUI(QWidget* widget)
    {
        setupUiGeology(widget);
        setupUiGeom(widget);
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
        Perm->setMinimum(0.01);
        Perm->setMaximum(1000);
        Perm->setSingleStep(1);
        Perm->setValue(0.1);
        m_layoutGeology->addWidget(m_labelPerm, 0, 0);
        m_layoutGeology->addWidget(Perm, 0, 1);

        m_labelPermFract = new QLabel("Perm fract");
        PermFract = new QDoubleSpinBox();
        PermFract->setDecimals(2);
        PermFract->setMinimum(0.01);
        PermFract->setMaximum(1000);
        PermFract->setSingleStep(1);
        PermFract->setValue(10);
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

        m_labelPerm->setText("Permeability");
        m_labelPerm->setToolTip("Reservoir permeability, d");

        m_labelPermFract->setText("Fract perm");
        m_labelPermFract->setToolTip("Fracture  permeability, d");

        m_labelPoroFract->setText("Fract poro");
        m_labelPoroFract->setToolTip("Fracture porosity");
    }

    void setupUiGeom(QWidget* widget)
    {
        m_gbGeom = new QGroupBox();
        // _mainLayout = new QVBoxLayout(widget);
        // _mainLayout->addWidget(_groupBox);
        m_layoutGeom = new QGridLayout(m_gbGeom);
        m_gbGeom->setLayout(m_layoutGeom);
        m_layoutGeom->setMargin(5);

        m_labelR = new QLabel("R");
        R = new QDoubleSpinBox();
        R->setDecimals(1);
        R->setMinimum(1);
        R->setMaximum(500);
        R->setSingleStep(10);
        R->setValue(50);
        m_layoutGeom->addWidget(m_labelR, 0, 0);
        m_layoutGeom->addWidget(R, 0, 1);

        m_labelL = new QLabel("L");
        L = new QDoubleSpinBox();
        L->setDecimals(1);
        L->setMinimum(1);
        L->setMaximum(1000);
        L->setSingleStep(10);
        L->setValue(500);
        m_layoutGeom->addWidget(m_labelL, 1, 0);
        m_layoutGeom->addWidget(L, 1, 1);

        m_labelDelta = new QLabel("Delta");
        Delta = new QDoubleSpinBox();
        Delta->setDecimals(3);
        Delta->setMinimum(1e-3);
        Delta->setMaximum(0.1);
        Delta->setSingleStep(1e-1);
        Delta->setValue(0.01);
        m_layoutGeom->addWidget(m_labelDelta, 2, 0);
        m_layoutGeom->addWidget(Delta, 2, 1);

        m_labelRw = new QLabel("Rw");
        Rw = new QDoubleSpinBox();
        Rw->setDecimals(1e-2);
        Rw->setMinimum(1e-2);
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

        m_labelDelta->setText("Delta");
        m_labelDelta->setToolTip("Fracture half thickness, m");

        m_labelL->setText("L");
        m_labelL->setToolTip("Reservoir lenght, m");

        m_labelR->setText("R");
        m_labelR->setToolTip("Reservoir radius, m");

        m_labelRw->setText("Rw");
        m_labelRw->setToolTip("Well radius, m");
    }
};

}

#endif
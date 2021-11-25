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
    QLabel* LabelPerm;
    QLabel* LabelPoroFract;
    QLabel* LabelPermFract;

    void setupUI(QWidget* widget)
    {
        setupUiGeology(widget);
        setupUiMain(widget);
    }

private:
    QWidget* m_window;
    QScrollArea* m_scrollArea;
    QVBoxLayout* m_layout;
    QGroupBox* m_gbGeology;
    QGridLayout* m_layoutGeology;

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
    }

    void setupUiGeology(QWidget* widget)
    {
        m_gbGeology = new QGroupBox();
        m_layoutGeology = new QGridLayout(m_gbGeology);
        m_gbGeology->setLayout(m_layoutGeology);

        m_layoutGeology->setMargin(5);

        LabelPerm = new QLabel("Permeability");
        Perm = new QDoubleSpinBox();
        Perm->setDecimals(2);
        Perm->setMinimum(0.01);
        Perm->setMaximum(1000);
        Perm->setSingleStep(1);
        Perm->setValue(0.1);
        m_layoutGeology->addWidget(LabelPerm, 0, 0);
        m_layoutGeology->addWidget(Perm, 0, 1);

        LabelPermFract = new QLabel("Perm fract");
        PermFract = new QDoubleSpinBox();
        PermFract->setDecimals(2);
        PermFract->setMinimum(0.01);
        PermFract->setMaximum(1000);
        PermFract->setSingleStep(1);
        PermFract->setValue(10);
        m_layoutGeology->addWidget(LabelPermFract, 1, 0);
        m_layoutGeology->addWidget(PermFract, 1, 1);

        LabelPoroFract = new QLabel("Porosity fract");
        PoroFract = new QDoubleSpinBox();
        PoroFract->setDecimals(1);
        PoroFract->setMinimum(0.1);
        PoroFract->setMaximum(0.7);
        PoroFract->setSingleStep(1e-1);
        PoroFract->setValue(0.2);
        m_layoutGeology->addWidget(LabelPoroFract, 2, 0);
        m_layoutGeology->addWidget(PoroFract, 2, 1);

        retranslateUiGeology(widget);
    }

    void retranslateUiGeology(QWidget* widget)
    {
        m_gbGeology->setTitle("Geology");
        m_gbGeology->setToolTip("Geology data");

        LabelPerm->setText("Permeability");
        LabelPerm->setToolTip("Reservoir permeability, d");

        LabelPermFract->setText("Fract perm");
        LabelPermFract->setToolTip("Fracture  permeability, d");

        LabelPoroFract->setText("Fract poro");
        LabelPoroFract->setToolTip("Fracture porosity");
    }
};

}

#endif
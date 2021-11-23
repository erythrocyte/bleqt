#ifndef BLE_GUI_WIDGETS_UI_GEOLOGYDATA_H_
#define BLE_GUI_WIDGETS_UI_GEOLOGYDATA_H_

#include <iostream>
#include <memory>

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {
class GeologyData {
public:
    QDoubleSpinBox* Perm;
    QDoubleSpinBox* PermFract;
    QDoubleSpinBox* PoroFract;
    QGridLayout* Layout;
    QLabel* LabelPerm;
    QLabel* LabelPoroFract;
    QLabel* LabelPermFract;

    void setupUi(QWidget* widget)
    {
        _groupBox = new QGroupBox();
        _mainLayout = new QVBoxLayout(widget);
        _mainLayout->addWidget(_groupBox);
        Layout = new QGridLayout(_groupBox);
        _groupBox->setLayout(Layout);

        Layout->setMargin(5);

        LabelPerm = new QLabel("Permeability");
        Perm = new QDoubleSpinBox();
        Perm->setDecimals(2);
        Perm->setMinimum(0.01);
        Perm->setMaximum(1000);
        Perm->setSingleStep(1);
        Perm->setValue(0.1);
        Layout->addWidget(LabelPerm, 0, 0);
        Layout->addWidget(Perm, 0, 1);

        LabelPermFract = new QLabel("Perm fract");
        PermFract = new QDoubleSpinBox();
        PermFract->setDecimals(2);
        PermFract->setMinimum(0.01);
        PermFract->setMaximum(1000);
        PermFract->setSingleStep(1);
        PermFract->setValue(10);
        Layout->addWidget(LabelPermFract, 1, 0);
        Layout->addWidget(PermFract, 1, 1);

        LabelPoroFract = new QLabel("Porosity fract");
        PoroFract = new QDoubleSpinBox();
        PoroFract->setDecimals(1);
        PoroFract->setMinimum(0.1);
        PoroFract->setMaximum(0.7);
        PoroFract->setSingleStep(1e-1);
        PoroFract->setValue(0.2);
        Layout->addWidget(LabelPoroFract, 2, 0);
        Layout->addWidget(PoroFract, 2, 1);

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        _groupBox->setTitle("Geology");
        _groupBox->setToolTip("Geology data");

        LabelPerm->setText("Permeability");
        LabelPerm->setToolTip("Reservoir permeability, d");

        LabelPermFract->setText("Fract perm");
        LabelPermFract->setToolTip("Fracture  permeability, d");

        LabelPoroFract->setText("Fract poro");
        LabelPoroFract->setToolTip("Fracture porosity");
    }

private:
    QGroupBox* _groupBox;
    QVBoxLayout* _mainLayout;
};

}

#endif

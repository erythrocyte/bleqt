#ifndef BLE_GUI_WIDGETS_UI_GEOMDATA_H_
#define BLE_GUI_WIDGETS_UI_GEOMDATA_H_

#include <iostream>
#include <memory>

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {
class GeomData {
public:
    QDoubleSpinBox* R;
    QDoubleSpinBox* L;
    QDoubleSpinBox* Delta;
    QDoubleSpinBox* Rw;
    QGridLayout* Layout;
    QLabel* LabelR;
    QLabel* LabelL;
    QLabel* LabelDelta;
    QLabel* LabelRw;

    void setupUi(QWidget* widget)
    {
        _groupBox = new QGroupBox();
        _mainLayout = new QVBoxLayout(widget);
        _mainLayout->addWidget(_groupBox);
        Layout = new QGridLayout(_groupBox);
        _groupBox->setLayout(Layout);

        Layout->setMargin(5);

        LabelR = new QLabel("R");
        R = new QDoubleSpinBox();
        R->setDecimals(1);
        R->setMinimum(1);
        R->setMaximum(500);
        R->setSingleStep(10);
        R->setValue(50);
        Layout->addWidget(LabelR, 0, 0);
        Layout->addWidget(R, 0, 1);

        LabelL = new QLabel("L");
        L = new QDoubleSpinBox();
        L->setDecimals(1);
        L->setMinimum(1);
        L->setMaximum(1000);
        L->setSingleStep(10);
        L->setValue(500);
        Layout->addWidget(LabelL, 1, 0);
        Layout->addWidget(L, 1, 1);

        LabelDelta = new QLabel("Delta");
        Delta = new QDoubleSpinBox();
        Delta->setDecimals(3);
        Delta->setMinimum(1e-3);
        Delta->setMaximum(0.1);
        Delta->setSingleStep(1e-1);
        Delta->setValue(0.01);
        Layout->addWidget(LabelDelta, 2, 0);
        Layout->addWidget(Delta, 2, 1);

        LabelRw = new QLabel("Rw");
        Rw = new QDoubleSpinBox();
        Rw->setDecimals(1e-2);
        Rw->setMinimum(1e-2);
        Rw->setMaximum(1);
        Rw->setSingleStep(1e-2);
        Rw->setValue(0.1);
        Layout->addWidget(LabelRw, 3, 0);
        Layout->addWidget(Rw, 3, 1);

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        _groupBox->setTitle("Geometry");
        _groupBox->setToolTip("Geometry data");

        LabelDelta->setText("Delta");
        LabelDelta->setToolTip("Fracture half thickness, m");

        LabelL->setText("L");
        LabelL->setToolTip("Reservoir lenght, m");

        LabelR->setText("R");
        LabelR->setToolTip("Reservoir radius, m");

        LabelRw->setText("Rw");
        LabelRw->setToolTip("Well radius, m");
    }

private:
    QGroupBox* _groupBox;
    QVBoxLayout* _mainLayout;
};

}

#endif

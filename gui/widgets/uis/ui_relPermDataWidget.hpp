#ifndef BLE_GUI_WIDGETS_UI_PHYSICDATA_H_
#define BLE_GUI_WIDGETS_UI_PHYSICDATA_H_

#include <iostream>
#include <memory>

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {
class RelPermData {
public:
    QDoubleSpinBox* MuWat;
    QDoubleSpinBox* MuOil;
    QDoubleSpinBox* N;
    QGridLayout* Layout;
    QLabel* LabelMuWat;
    QLabel* LabelMuOil;
    QLabel* LabelN;

    void setupUi(QWidget* widget)
    {
        _groupBox = new QGroupBox();
        _mainLayout = new QVBoxLayout(widget);
        _mainLayout->addWidget(_groupBox);
        Layout = new QGridLayout(_groupBox);
        _groupBox->setLayout(Layout);

        Layout->setMargin(5);

        MuWat = new QDoubleSpinBox();
        MuOil = new QDoubleSpinBox();
        N = new QDoubleSpinBox();

        LabelMuOil = new QLabel();
        LabelMuWat = new QLabel();
        LabelN = new QLabel();

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        _groupBox->setTitle("Relative permeability data");
        _groupBox->setToolTip("Relative permeability data");

        LabelMuWat->setText("Water visc");
        LabelMuWat->setToolTip("Water viscosity, Pa*s");

        LabelMuWat->setText("Oil visc");
        LabelMuWat->setToolTip("Oil viscosity, Pa*s");

        LabelN->setText("N");
        LabelN->setToolTip("Relative permeability degree");
    }

private:
    QGroupBox* _groupBox;
    QVBoxLayout* _mainLayout;
};

}

#endif

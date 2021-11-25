#ifndef BLE_GUI_WIDGETS_UI_SHOCKFRONTSETTS_H_
#define BLE_GUI_WIDGETS_UI_SHOCKFRONTSETTS_H_

#include <iostream>
#include <memory>

#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {
class ShockFrontSetts {
public:
    QLabel* shockFrontValue;
    QCheckBox* showCurve;

    void setupUi(QWidget* widget)
    {
        _groupBox = new QGroupBox("Shock front");
        _mainLayout = new QVBoxLayout(widget);
        _mainLayout->addStretch();
        _mainLayout->setDirection(QVBoxLayout::BottomToTop);
        widget->setLayout(_mainLayout);
        _mainLayout->addWidget(_groupBox);

        _layout = new QVBoxLayout(_groupBox);
        _groupBox->setLayout(_layout);

        shockFrontValue = new QLabel("Shock front value: -");
        _layout->addWidget(shockFrontValue);

        showCurve = new QCheckBox();

        _layout->addWidget(showCurve);

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        _groupBox->setTitle("Shock front");
        _groupBox->setToolTip("Shock front");

        showCurve->setText("Show shock front saturation");
        showCurve->setToolTip("Show shock front saturation");
    }

private:
    QGroupBox* _groupBox;
    QVBoxLayout* _mainLayout;
    QVBoxLayout* _layout;
};

}

#endif
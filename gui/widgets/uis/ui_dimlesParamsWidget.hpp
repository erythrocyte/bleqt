#ifndef BLE_GUI_WIDGETS_UI_DIMLESSPARAMS_H_
#define BLE_GUI_WIDGETS_UI_DIMLESSPARAMS_H_

#include <iostream>
#include <memory>

#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {
class DimlessParams {
public:
    QLabel* valueM;

    void setupUi(QWidget* widget)
    {
        _groupBox = new QGroupBox("Dimless params");
        _mainLayout = new QVBoxLayout(widget);
        _mainLayout->addStretch();
        _mainLayout->setDirection(QVBoxLayout::BottomToTop);
        widget->setLayout(_mainLayout);
        _mainLayout->addWidget(_groupBox);

        _layout = new QVBoxLayout(_groupBox);
        _groupBox->setLayout(_layout);

        valueM = new QLabel("Shock front value: -");
        _layout->addWidget(valueM);

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        _groupBox->setTitle("Dimless params");
        _groupBox->setToolTip("Dimless params");
    }

private:
    QGroupBox* _groupBox;
    QVBoxLayout* _mainLayout;
    QVBoxLayout* _layout;
};

}

#endif
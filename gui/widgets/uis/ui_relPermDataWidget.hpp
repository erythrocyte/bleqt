#ifndef BLEGUI_WIDGETS_UI_PHYSICDATA_H_
#define BLEGUI_WIDGETS_UI_PHYSICDATA_H_

#include <iostream>
#include <memory>

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

namespace ble_gui::widgets {
namespace UI {
    class RelPermData {
    public:
        QDoubleSpinBox* Kmu;
        QDoubleSpinBox* N;
        QGridLayout* Layout;
        QLabel* LabelKmu;
        QLabel* LabelN;

        void setupUi(QWidget* widget)
        {
            _groupBox = new QGroupBox();
            _mainLayout = new QVBoxLayout(widget);
            _mainLayout->addWidget(_groupBox);
            Layout = new QGridLayout(_groupBox);
            _groupBox->setLayout(Layout);

            Layout->setMargin(5);

            Kmu = new QDoubleSpinBox();
            N = new QDoubleSpinBox();

            LabelKmu = new QLabel();
            LabelN = new QLabel();

            retranslateUi(widget);
        }

        void retranslateUi(QWidget* widget)
        {
            _groupBox->setTitle("Relative permeability data");
            _groupBox->setToolTip("Relative permeability data");

            LabelKmu->setText("Kmu");
            LabelKmu->setToolTip("Kmu");

            LabelN->setText("N");
            LabelN->setToolTip("N");
        }

    private:
        QGroupBox* _groupBox;
        QVBoxLayout* _mainLayout;
    };
}

}

#endif

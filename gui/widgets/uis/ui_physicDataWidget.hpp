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

namespace ble_gui {
namespace widgets {
    namespace UI {
        class PhysicData {
        public:
            QDoubleSpinBox* Kmu;
            QDoubleSpinBox* Nwat;
            QDoubleSpinBox* Noil;
            QGridLayout* Layout;
            QLabel* LabelKmu;
            QLabel* LabelNwat;
            QLabel* LabelNoil;

            void setupUi(QWidget* widget)
            {
                _groupBox = new QGroupBox();
                _mainLayout = new QVBoxLayout(widget);
                _mainLayout->addWidget(_groupBox);
                Layout = new QGridLayout(_groupBox);
                _groupBox->setLayout(Layout);

                Layout->setMargin(5);

                Kmu = new QDoubleSpinBox();
                Nwat = new QDoubleSpinBox();
                Noil = new QDoubleSpinBox();

                LabelKmu = new QLabel();
                LabelNwat = new QLabel();
                LabelNoil = new QLabel();

                retranslateUi(widget);
            }

            void retranslateUi(QWidget* widget)
            {
                _groupBox->setTitle("Physical data");
                _groupBox->setToolTip("Physical data");

                LabelKmu->setText("Kmu");
                LabelKmu->setToolTip("Kmu");

                LabelNwat->setText("Nwat");
                LabelNwat->setToolTip("Nwat");

                LabelNoil->setText("Noil");
                LabelNoil->setToolTip("Noil");
            }

        private:
            QGroupBox* _groupBox;
            QVBoxLayout* _mainLayout;
        };
    }
}
}

#endif
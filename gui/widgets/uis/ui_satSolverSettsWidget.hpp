#ifndef BLEGUI_WIDGETS_UI_SATSOLVERSETTS_H_
#define BLEGUI_WIDGETS_UI_SATSOLVERSETTS_H_

#include <iostream>
#include <memory>

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

namespace ble_gui {
namespace widgets {
    namespace UI {
        class SatSolverSetts {
        public:
            QDoubleSpinBox* Curant;
            QSpinBox* RecalcPressN;
            QComboBox* SolverType;

            void setupUi(QWidget* widget)
            {
                _groupBox = new QGroupBox();
                _mainLayout = new QVBoxLayout(widget);
                _mainLayout->addWidget(_groupBox);
                _layout = new QGridLayout(_groupBox);
                _groupBox->setLayout(_layout);

                _layout->setMargin(5);

                Curant = new QDoubleSpinBox();
                Curant->setDecimals(4);
                Curant->setMinimum(1e-6);
                Curant->setMaximum(1e6);
                Curant->setSingleStep(0.001);
                Curant->setValue(0.1);
                _layout->addWidget(Curant, 0, 1);

                _curantLabel = new QLabel();
                _layout->addWidget(_curantLabel, 0, 0);

                RecalcPressN = new QSpinBox();
                RecalcPressN->setMinimum(1);
                RecalcPressN->setMaximum(100);
                RecalcPressN->setValue(10);
                _layout->addWidget(RecalcPressN, 1, 1);

                _recalcPressLabel = new QLabel();
                _layout->addWidget(_recalcPressLabel, 1, 0);

                SolverType = new QComboBox();
                SolverType->setEnabled(false);
                _layout->addWidget(SolverType, 2, 1);

                _solverTypeLabel = new QLabel();
                _layout->addWidget(_solverTypeLabel, 2, 0);

                retranslateUi(widget);
            }

            void retranslateUi(QWidget* widget)
            {
                _groupBox->setTitle("Saturation solver");
                _groupBox->setToolTip("Saturation solver");

                _curantLabel->setText("Curant number");
                _curantLabel->setToolTip("Curant number");

                _recalcPressLabel->setText("Calc press step");
                _recalcPressLabel->setToolTip("Calc press step");

                _solverTypeLabel->setText("Solver type");
                _solverTypeLabel->setToolTip("Solver type");
            }

        private:
            QGroupBox* _groupBox;
            QVBoxLayout* _mainLayout;
            QGridLayout* _layout;
            QLabel* _curantLabel;
            QLabel* _recalcPressLabel;
            QLabel* _solverTypeLabel;
        };
    }
}
}

#endif
#ifndef BLE_GUI_WIDGETS_UI_SATSOLVERSETTS_H_
#define BLE_GUI_WIDGETS_UI_SATSOLVERSETTS_H_

#include <iostream>
#include <memory>

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QWidget>

namespace ble::gui::widgets::UI {
class SatSolverSetts {
public:
    QDoubleSpinBox* Curant;
    QSpinBox* RecalcPressN;
    QComboBox* SolverType;
    QCheckBox* NeedSaturSolve;
    QSpinBox* SaveSaturField;
    QSpinBox* MaxIter;
    QCheckBox* NeedStopFwPseudoConst;
    QDoubleSpinBox* FwDelta;
    QSpinBox* FwDeltaIter;
    QCheckBox* NeedStopFwShoreWellConverge;
    QDoubleSpinBox* FwShoreWellConverge;

    void setupUi(QWidget* widget)
    {
        _groupBox = new QGroupBox();
        _mainLayout = new QVBoxLayout(widget);
        _mainLayout->addStretch();
        _mainLayout->setDirection(QVBoxLayout::BottomToTop);
        _mainLayout->addWidget(_groupBox);
        _layout = new QGridLayout(_groupBox);
        _groupBox->setLayout(_layout);

        _layout->setMargin(5);

        _curantLabel = new QLabel();
        Curant = new QDoubleSpinBox();
        Curant->setDecimals(7);
        Curant->setMinimum(1e-6);
        Curant->setMaximum(1e6);
        Curant->setSingleStep(0.001);
        Curant->setValue(0.00005);
        _layout->addWidget(_curantLabel, 0, 0);
        _layout->addWidget(Curant, 0, 1);

        _recalcPressLabel = new QLabel();
        RecalcPressN = new QSpinBox();
        RecalcPressN->setMinimum(1);
        RecalcPressN->setMaximum(100);
        RecalcPressN->setValue(10);
        _layout->addWidget(_recalcPressLabel, 1, 0);
        _layout->addWidget(RecalcPressN, 1, 1);

        SolverType = new QComboBox();
        SolverType->setEnabled(false);
        _layout->addWidget(SolverType, 2, 1);

        _solverTypeLabel = new QLabel();
        _layout->addWidget(_solverTypeLabel, 2, 0);

        NeedSaturSolve = new QCheckBox("Solve saturation");
        NeedSaturSolve->setChecked(true);
        _layout->addWidget(NeedSaturSolve, 3, 0, 1, 2);

        m_saveDataStep = new QLabel();
        SaveSaturField = new QSpinBox();
        SaveSaturField->setMinimum(1);
        SaveSaturField->setMaximum(100000);
        SaveSaturField->setValue(100);
        _layout->addWidget(m_saveDataStep, 4, 0);
        _layout->addWidget(SaveSaturField, 4, 1);

        m_maxIterLabel = new QLabel("Max iteration");
        MaxIter = new QSpinBox();
        MaxIter->setMinimum(1);
        MaxIter->setMaximum(100000000);
        MaxIter->setValue(100000000);
        _layout->addWidget(m_maxIterLabel, 5, 0);
        _layout->addWidget(MaxIter, 5, 1);

        NeedStopFwPseudoConst = new QCheckBox("Stop watercut change");
        NeedStopFwPseudoConst->setChecked(false);
        _layout->addWidget(NeedStopFwPseudoConst, 6, 0, 1, 2);

        m_fwDeltaLabel = new QLabel();
        FwDelta = new QDoubleSpinBox();
        FwDelta->setDecimals(8);
        FwDelta->setMinimum(1e-8);
        FwDelta->setMaximum(100);
        FwDelta->setSingleStep(1e-8);
        FwDelta->setValue(5);
        _layout->addWidget(m_fwDeltaLabel, 7, 0);
        _layout->addWidget(FwDelta, 7, 1);

        m_fwDeltaIterLabel = new QLabel("Max iteration");
        FwDeltaIter = new QSpinBox();
        FwDeltaIter->setMinimum(1);
        FwDeltaIter->setMaximum(1e6);
        FwDeltaIter->setValue(10000);
        _layout->addWidget(m_fwDeltaIterLabel, 8, 0);
        _layout->addWidget(FwDeltaIter, 8, 1);

        NeedStopFwShoreWellConverge = new QCheckBox("Watercut shore|well on converge");
        NeedStopFwShoreWellConverge->setChecked(false);
        _layout->addWidget(NeedStopFwShoreWellConverge, 9, 0, 1, 2);

        m_fwShoreWellConvergeLabel = new QLabel();
        FwShoreWellConverge = new QDoubleSpinBox();
        FwShoreWellConverge->setDecimals(8);
        FwShoreWellConverge->setMinimum(1e-8);
        FwShoreWellConverge->setMaximum(100);
        FwShoreWellConverge->setSingleStep(1e-8);
        FwShoreWellConverge->setValue(1e-5);
        _layout->addWidget(m_fwShoreWellConvergeLabel, 10, 0);
        _layout->addWidget(FwShoreWellConverge, 10, 1);

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        // _groupBox->setTitle("Saturation");
        // _groupBox->setToolTip("Saturation");

        _curantLabel->setText("Curant number");
        _curantLabel->setToolTip("Curant number");

        _recalcPressLabel->setText("Calc press step");
        _recalcPressLabel->setToolTip("Calculate pressure every N saturation calc step");

        _solverTypeLabel->setText("Solver type");
        _solverTypeLabel->setToolTip("Solver type");

        NeedSaturSolve->setText("Solve saturation");
        NeedSaturSolve->setToolTip("Solve saturation");

        m_saveDataStep->setText("Save data");
        m_saveDataStep->setToolTip("Save data step");

        m_maxIterLabel->setText("Max iteration");
        m_maxIterLabel->setToolTip("Max iteration count to stop calc");

        m_fwDeltaLabel->setText("Watercut delta");
        m_fwDeltaLabel->setToolTip("Watercut change delta");

        m_fwDeltaIterLabel->setText("Watercut delta iter");
        m_fwDeltaIterLabel->setToolTip("Watercut change for small delta iter count");

        NeedStopFwPseudoConst->setText("Stop watercut change");
        NeedStopFwPseudoConst->setToolTip("Stop when watercut change less than delta for long iter");

        NeedStopFwShoreWellConverge->setText("Watercut shore|well on converge");
        NeedStopFwShoreWellConverge->setToolTip("Stop when watercut shore|well converged");

        m_fwShoreWellConvergeLabel->setText("Fw shore|well delta, %");
        m_fwShoreWellConvergeLabel->setToolTip("Watercut shore|well residual max value to stop calculation");
    }

private:
    QGroupBox* _groupBox;
    QVBoxLayout* _mainLayout;
    QGridLayout* _layout;
    QLabel* _curantLabel;
    QLabel* _recalcPressLabel;
    QLabel* _solverTypeLabel;
    QLabel* m_saveDataStep;
    QLabel* m_maxIterLabel;
    QLabel* m_fwDeltaLabel;
    QLabel* m_fwDeltaIterLabel;
    QLabel* m_fwShoreWellConvergeLabel;
};

}

#endif
#include "satSolverSettsWidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace ble_gui
{
    SaturSolverSettsWidget::SaturSolverSettsWidget(QWidget *parent)
    {
        QGroupBox* groupBox = new QGroupBox("Saturation solver");
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(groupBox);
        QGridLayout *layout = new QGridLayout(groupBox);
        groupBox->setLayout(layout);

        layout->setMargin(5);

		Curant = new QDoubleSpinBox();
        Curant->setDecimals(4);
		Curant->setMinimum(1e-6);
		Curant->setMaximum(1e6);
		Curant->setSingleStep(0.001);
		Curant->setValue(0.001);
		layout->addWidget(Curant, 0, 1);

		QLabel *curantLabel = new QLabel("Curant number");
		layout->addWidget(curantLabel, 0, 0);

		RecalcPressN = new QSpinBox();
		RecalcPressN->setMinimum(1);
		RecalcPressN->setMaximum(100);
		RecalcPressN->setValue(10);
		layout->addWidget(RecalcPressN, 1, 1);

		QLabel *recalcPressLabel = new QLabel("Calc press step");
		layout->addWidget(recalcPressLabel, 1, 0);

		SolverType = new QComboBox();
		layout->addWidget(SolverType, 2, 1);

		QLabel *solverTypeLabel = new QLabel("Solver type");
		layout->addWidget(solverTypeLabel, 2, 0);
    }
} // namespace ble_gui

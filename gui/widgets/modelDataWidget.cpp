#include "modelDataWidget.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

ble_gui::widgets::ModelDataWidget::ModelDataWidget(QWidget *parent)
	: QWidget(parent)
{
	QGroupBox *groupBox = new QGroupBox("Modeling data");
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(groupBox);
	QGridLayout *layout = new QGridLayout(groupBox);
	groupBox->setLayout(layout);

	layout->setMargin(5);

	Period = new QDoubleSpinBox();
	Period->setMinimum(0.1);
	Period->setMaximum(1e10);
	Period->setSingleStep(0.1);
	Period->setValue(30);
	layout->addWidget(Period, 0, 1);

	QLabel *periodLabel = new QLabel("Period");
	layout->addWidget(periodLabel, 0, 0);
}

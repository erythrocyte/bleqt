#include "modelDataWidget.hpp"

#include <QGridLayout>
#include <QLabel>

namespace ble_gui {

ModelDataWidget::ModelDataWidget(QWidget* parent)
	: QWidget(parent)
{
	QGridLayout* layout = new QGridLayout(this);
	layout->setMargin(0);

	Period = new QDoubleSpinBox();
	Period->setMinimum(0.1);
	Period->setMaximum(1e20);
	Period->setSingleStep(0.1);
	Period->setValue(5.0);
	layout->addWidget(Period, 0, 1);

	QLabel* periodLabel = new QLabel("Period");
	layout->addWidget(periodLabel, 0, 0);
}

}

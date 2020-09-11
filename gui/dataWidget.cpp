#include "dataWidget.hpp"

#include <QVBoxLayout>

namespace ble_gui {

DataWidget::DataWidget(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);

	PhysData = new PhysDataWidget();
	layout->addWidget(PhysData);

	ModelData = new ModelDataWidget();
	layout->addWidget(ModelData);

	SaturSolverSetts = new SaturSolverSettsWidget();
	layout->addWidget(SaturSolverSetts);

	this->setLayout(layout);
}

}

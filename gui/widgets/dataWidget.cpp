#include "dataWidget.hpp"

#include <QVBoxLayout>

ble_gui::widgets::DataWidget::DataWidget(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	PhysData = new PhysDataWidget();
	layout->addWidget(PhysData);

	ModelData = new ModelDataWidget();
	layout->addWidget(ModelData);

	SaturSolverSetts = new SaturSolverSettsWidget();
	layout->addWidget(SaturSolverSetts);

	GridSetts = new GridSettsWidget();
	layout->addWidget(GridSetts);

	ShockFrontSetts = new ShockFrontSettsWidget();
	layout->addWidget(ShockFrontSetts);

	this->setLayout(layout);
}

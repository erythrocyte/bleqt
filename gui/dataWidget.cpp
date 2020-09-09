#include "dataWidget.hpp"

#include <QHBoxLayout>

namespace ble_gui {

DataWidget::DataWidget(QWidget *parent)
	: QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);

	ModelData = new ModelDataWidget();
	layout->addWidget(ModelData);

	this->setLayout(layout);
}

}

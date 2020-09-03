#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "test.hpp"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QWidget widget;
	widget.resize(640, 480);

	std::string labelText = ble_src::getHelloString();
	QString qstr = QString::fromStdString(labelText);

	widget.setWindowTitle("BLE Solver");

	QGridLayout *gridLayout = new QGridLayout(&widget);

	QLabel * label = new QLabel(qstr);
	label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	gridLayout->addWidget(label);

	widget.show();

	return app.exec();
}

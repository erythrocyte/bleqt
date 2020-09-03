#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QWidget widget;
	widget.resize(640, 480);

	widget.setWindowTitle("BLE Solver");

	QGridLayout* gridLayout = new QGridLayout(&widget);

	QLabel* label = new QLabel("Test label");
	label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
	gridLayout->addWidget(label);

	widget.show();

	return app.exec();
}

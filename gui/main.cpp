#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "bleFrame.hpp"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	ble_gui::views::BleFrame mainWindow;
	mainWindow.show();

	return app.exec();
}

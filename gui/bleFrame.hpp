#ifndef BLE_GUI_BLEFRAME_H_
#define BLE_GUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "grid.hpp"
#include "inputData.hpp"

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

namespace ble_gui{

namespace Ui {
	class BleFrame;
}

class BleFrame : public QMainWindow
{
	Q_OBJECT
	public:
		explicit BleFrame(QWidget* parent = nullptr);
		virtual ~BleFrame();

	private slots:
		void handleRunButton();

	private:
		QWidget* central;
		QPushButton* run_button;
		QGridLayout* layout;
		QLabel* label;

		std::shared_ptr<ble_src::Grid> grd;
		std::shared_ptr<ble_src::InputData> data;

		void getDefaultData();
		void makeGrid();
};

}

#endif

#ifndef BLE_GUI_PHYSICDATAWIDGET_H_
#define BLE_GUI_PHYSICDATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>

namespace ble_gui {

class PhysDataWidget: public QWidget {
	Q_OBJECT
	public:
		PhysDataWidget(QWidget* parent = nullptr);
		~PhysDataWidget() {}

		QDoubleSpinBox* Kmu;
		QDoubleSpinBox* Nwat;
		QDoubleSpinBox* Noil;
		QDoubleSpinBox* Poro;
		QDoubleSpinBox* Perm;
};

}

#endif

#ifndef BLE_GUI_MODELDATAWIDGET_H_
#define BLE_GUI_MODELDATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>

namespace ble_gui {

class ModelDataWidget: public QWidget {
	Q_OBJECT
	public:
		ModelDataWidget(QWidget* parent = nullptr);
		~ModelDataWidget() {}
		QDoubleSpinBox* Period;
};

}

#endif
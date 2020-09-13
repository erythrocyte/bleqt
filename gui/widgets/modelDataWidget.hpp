#ifndef BLEGUI_WIDGETS_MODELDATAWIDGET_H_
#define BLEGUI_WIDGETS_MODELDATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>

namespace ble_gui
{
	namespace widgets
	{
		class ModelDataWidget : public QWidget
		{
			Q_OBJECT
		public:
			ModelDataWidget(QWidget *parent = nullptr);
			~ModelDataWidget() {}
			QDoubleSpinBox *Period;
		};
	} // namespace widgets
} // namespace ble_gui

#endif

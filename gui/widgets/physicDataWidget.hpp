#ifndef BLEGUI_WIDGETS_PHYSICDATAWIDGET_H_
#define BLEGUI_WIDGETS_PHYSICDATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>

namespace ble_gui
{
	namespace widgets
	{
		class PhysDataWidget : public QWidget
		{
			Q_OBJECT
		public:
			PhysDataWidget(QWidget *parent = nullptr);
			~PhysDataWidget() {}

			QDoubleSpinBox *Kmu;
			QDoubleSpinBox *Nwat;
			QDoubleSpinBox *Noil;
			QDoubleSpinBox *Poro;
			QDoubleSpinBox *Perm;
		};
	} // namespace widgets
} // namespace ble_gui

#endif
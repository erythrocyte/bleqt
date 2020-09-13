#ifndef BLEGUI_WIDGETS_DATAWIDGET_H_
#define BLEGUI_WIDGETS_DATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "modelDataWidget.hpp"
#include "physicDataWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "gridSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"

namespace ble_gui
{
	namespace widgets
	{
		class DataWidget : public QWidget
		{
			Q_OBJECT

		public:
			DataWidget(QWidget *parent = nullptr);
			~DataWidget() {}

			ModelDataWidget *ModelData;
			PhysDataWidget *PhysData;
			SaturSolverSettsWidget *SaturSolverSetts;
			GridSettsWidget *GridSetts;
			ShockFrontSettsWidget *ShockFrontSetts;
		};
	} // namespace widgets
} // namespace ble_gui

#endif

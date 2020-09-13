#ifndef BLEGUI_BLEFRAME_H_
#define BLEGUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "inputData.hpp"
#include "dynamicData.hpp"
#include "grid.hpp"
#include "bleCalc.hpp"

#include "dataWidget.hpp"
#include "resultDataVisualWidget.hpp"

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QStatusBar>
#include <QProgressBar>
#include <QDockWidget>

namespace ble_gui
{
	namespace views
	{
		class BleFrame : public QMainWindow
		{
			Q_OBJECT
		public:
			explicit BleFrame(QWidget *parent = nullptr);
			virtual ~BleFrame();

		private:
			QWidget *central;
			QGridLayout *layout;
			widgets::DataWidget *dataWidget;
			widgets::ResultDataVisualWidget *resultDataVisual;
			QMenu *menu;
			QStatusBar *statusBar;
			QLabel *statusLabel;
			QProgressBar *statusProgressBar;
			QDockWidget *_dock;

			std::shared_ptr<ble_src::Grid> _grd;
			std::shared_ptr<ble_src::InputData> _data;
			std::shared_ptr<ble_src::BleCalc> _solver;

			std::vector<double> solve_press(const std::vector<double> &s);
			std::vector<double> solve_satur(const double tau, const std::vector<double> &s);

			void set_default_data();
			void make_grid();
			void set_initial_cond();
			void update_time_info(int index);
			void set_signals();
			void update_progress(double perc);

			void set_menu();
			void set_settings_widget();
			void set_visual_data_widget();

		private slots:
			void handleRunButton();
			void updateInputData();
			void showScCheckedChange();
			void update_sc();
		};
	} // namespace views
} // namespace ble_gui

#endif

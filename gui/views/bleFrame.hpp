#ifndef BLE_GUI_BLEFRAME_H_
#define BLE_GUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "inputData.hpp"
#include "dynamicData.hpp"
#include "grid.hpp"

#include "dataWidget.hpp"

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QLineEdit>
#include <QSlider>
#include <QMenu>
#include <QStatusBar>
#include <QProgressBar>

using namespace QtCharts;

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
			std::shared_ptr<ble_src::Grid> grd;
			std::shared_ptr<ble_src::InputData> data;
			bool graphFirst = true;
			std::vector<std::shared_ptr<ble_src::DynamicData>> results;

			std::vector<double> solve_press(const std::vector<double> &s);
			std::vector<double> solve_satur(const double tau, const std::vector<double> &s);

			void set_default_data();
			void make_grid();
			void set_initial_cond();
			void fill_time_series(bool init, int index);
			void update_time_info(int index);
			void fill_sc_series();
			void set_signals();
			void update_sc_series(bool init);

		private slots:
			void handleRunButton();
			void handleSliderValueChange();
			void updateInputData();
			void showScCheckedChange();
			void update_sc();

		private:
			QWidget *central;
			QGridLayout *layout;
			QChartView *chartView;
			QChart *chart;
			QLineSeries *series_press;
			QLineSeries *series_sat_num;
			QLineSeries *series_sat_an;
			QLineSeries *series_sc;
			QValueAxis *axisX;
			QValueAxis *axisYPress;
			QValueAxis *axisYSat;
			QSlider *slider;
			QLabel *label;
			DataWidget *dataWidget;
			QMenu *menu;
			QStatusBar *statusBar;
			QLabel *statusLabel;
			QProgressBar *statusProgressBar;
		};
	} // namespace views
} // namespace ble_gui

#endif

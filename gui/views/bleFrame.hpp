#ifndef BLEGUI_BLEFRAME_H_
#define BLEGUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "inputData.hpp"
#include "dynamicData.hpp"
#include "grid.hpp"
#include "bleCalc.hpp"

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
			widgets::DataWidget *dataWidget;
			QMenu *menu;
			QStatusBar *statusBar;
			QLabel *statusLabel;
			QProgressBar *statusProgressBar;

			std::shared_ptr<ble_src::Grid> _grd;
			std::shared_ptr<ble_src::InputData> _data;
			std::shared_ptr<ble_src::BleCalc> _solver;

			std::vector<double> solve_press(const std::vector<double> &s);
			std::vector<double> solve_satur(const double tau, const std::vector<double> &s);

			void set_default_data();
			void make_grid();
			void set_initial_cond();
			void fill_time_series(bool init, const std::shared_ptr<ble_src::DynamicData> d);
			void update_time_info(int index);
			void fill_sc_series();
			void set_signals();
			void update_sc_series(bool init);
			void update_progress(double perc);

		private slots:
			void handleRunButton();
			void handleSliderValueChange();
			void updateInputData();
			void showScCheckedChange();
			void update_sc();
		};
	} // namespace views
} // namespace ble_gui

#endif

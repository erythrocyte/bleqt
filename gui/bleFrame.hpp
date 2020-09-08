#ifndef BLE_GUI_BLEFRAME_H_
#define BLE_GUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "grid.hpp"
#include "inputData.hpp"
#include "dynamicData.hpp"

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

using namespace QtCharts;

namespace ble_gui{

//namespace Ui {
	//class BleFrame;
//}

class BleFrame : public QMainWindow
{
	Q_OBJECT
	public:
		explicit BleFrame(QWidget* parent = nullptr);
		virtual ~BleFrame();

	private slots:
		void handleRunButton();
		void handleSliderValueChange();
		void updateInputData();

	private:
		QWidget* central;
		QGridLayout* layout;
		QChartView* chartView;
		QChart* chart;
		QLineSeries* series_press;
		QLineSeries* series_sat_num;
		QValueAxis* axisX;
		QValueAxis* axisYPress;
		QValueAxis* axisYSat;
		QSlider* slider;
		QLabel* label;
		DataWidget* dataWidget;
		QMenu *menu;

		std::shared_ptr<ble_src::Grid> grd;
		std::shared_ptr<ble_src::InputData> data;

		std::vector<std::shared_ptr<ble_src::DynamicData>> results;

		void get_default_data();
		void make_grid();
		void set_initial_cond();
		std::vector<double> solve_press(const std::vector<double>& s);
		std::vector<double> solve_satur(const double tau, const std::vector<double>& s);

		void fill_time_series(int index);

		void update_time_info(int index);
};

}

#endif

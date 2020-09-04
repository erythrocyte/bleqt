#ifndef BLE_GUI_BLEFRAME_H_
#define BLE_GUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "grid.hpp"
#include "inputData.hpp"
#include "dynamicData.hpp"

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

using namespace QtCharts;

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
		QChartView* chartView;
		QChart* chart;
		QLineSeries* series_press;
		QValueAxis *axisX;
		QValueAxis *axisYPress;

		std::shared_ptr<ble_src::Grid> grd;
		std::shared_ptr<ble_src::InputData> data;

		std::vector<std::shared_ptr<ble_src::DynamicData>> results;

		void get_default_data();
		void make_grid();
		void set_initial_cond();
		std::vector<double> solve_press(const std::vector<double>& s);
		std::vector<double> solve_satur();

		void fill_time_series(int index);
};

}

#endif

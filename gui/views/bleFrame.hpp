#ifndef BLEGUI_BLEFRAME_H_
#define BLEGUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "bleCalc.hpp"
#include "bleResultData.hpp"
#include "dynamicData.hpp"
#include "grid.hpp"
#include "inputData.hpp"

#include "dataWidget.hpp"
#include "fluidParamsWidget.hpp"
#include "resultDataWidget.hpp"
#include "ui_bleFrame.hpp"

#include <QDockWidget>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>

namespace ble_gui::views {

class BleFrame : public QMainWindow, private UI::UI_BleFrame { //, public IBleFrame {
    Q_OBJECT
public:
    explicit BleFrame(QWidget* parent = nullptr);

    ~BleFrame() { delete ui; }

    void run() { show(); }

    void set_widgets(std::shared_ptr<widgets::FluidParamsWidget> fluidParamsVisual); 
        // std::shared_ptr<widgets::DataWidget> dataWidget);

// signals:
//     void update_fluid_view(
//         const std::shared_ptr<ble_src::PhysData> physData,
//         double sc);

private:
    UI::UI_BleFrame* ui;
//     QWidget* central;
//     QGridLayout* layout;
//     std::shared_ptr<widgets::DataWidget> _dataWidget;
//     widgets::ResultDataVisualWidget* resultDataVisual;
//     QMenu* menu;
//     QStatusBar* statusBar;
//     QLabel* statusLabel;
//     QProgressBar* statusProgressBar;
//     QDockWidget* _dock;

//     std::shared_ptr<ble_src::Grid> _grd;
//     std::shared_ptr<ble_src::InputData> _data;
//     std::shared_ptr<ble_src::BleCalc> _solver;

//     std::vector<double> solve_press(const std::vector<double>& s);
//     std::vector<double> solve_satur(const double tau, const std::vector<double>& s);

//     void set_default_data();
//     void make_grid();
//     void set_initial_cond();
//     void update_time_info(int index);
//     void set_signals();
//     void update_progress(double perc);

//     void set_menu();
//     void set_settings_widget();
//     void set_status_bar();

private slots:
    void handleRunButton();
//     void updateInputData();
//     void showScCheckedChange(bool);
//     void update_static_visual();
};

} // namespace ble_gui::views

#endif

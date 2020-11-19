#ifndef BLEGUI_BLEFRAME_H_
#define BLEGUI_BLEFRAME_H_

#include <iostream>
#include <memory>

#include "ibleFrame.hpp"

#include "bleCalc.hpp"
#include "bleResultData.hpp"
#include "dynamicData.hpp"
#include "grid.hpp"
#include "inputData.hpp"

#include "dataWidget.hpp"
#include "fluidParamsWidget.hpp"
#include "resultDataWidget.hpp"

#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QProgressBar>
#include <QStatusBar>

namespace ble_gui {
namespace views {
    class BleFrame : public QMainWindow, public IBleFrame {
        Q_OBJECT
    public:
        explicit BleFrame(QWidget* parent = nullptr);
        virtual ~BleFrame();

        virtual void run() { show(); }

        virtual void set_widgets(std::shared_ptr<widgets::FluidParamsVisualWidget> fluidParamsVisual);

    private:
        QWidget* central;
        QGridLayout* layout;
        widgets::DataWidget* dataWidget;
        widgets::ResultDataVisualWidget* resultDataVisual;
        // widgets::FluidParamsVisualWidget* fluidParamsVisual;
        QMenu* menu;
        QStatusBar* statusBar;
        QLabel* statusLabel;
        QProgressBar* statusProgressBar;
        QDockWidget* _dock;

        std::shared_ptr<ble_src::Grid> _grd;
        std::shared_ptr<ble_src::InputData> _data;
        std::shared_ptr<ble_src::BleCalc> _solver;

        std::vector<double> solve_press(const std::vector<double>& s);
        std::vector<double> solve_satur(const double tau, const std::vector<double>& s);

        void set_default_data();
        void make_grid();
        void set_initial_cond();
        void update_time_info(int index);
        void set_signals();
        void update_progress(double perc);

        void set_menu();
        void set_settings_widget();
        void set_status_bar();

    private slots:
        void handleRunButton();
        void updateInputData();
        void showScCheckedChange(bool);
        void update_static_visual();
    };
} // namespace views
} // namespace ble_gui

#endif

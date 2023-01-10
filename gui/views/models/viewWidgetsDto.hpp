#ifndef BLE_GUI_VIEWS_MODELS_VIEWWIDGETSDTO_H_
#define BLE_GUI_VIEWS_MODELS_VIEWWIDGETSDTO_H_

#include <iostream>
#include <memory>

#include "boundVisualWidget.hpp"
#include "conditionsWidget.hpp"
#include "dataWidget.hpp"
#include "dimlesParamsWidget.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "fwVisualWidget.hpp"
#include "gridSettsWidget.hpp"
#include "resultDataWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"
#include "tauVisualWidget.hpp"
#include "wellWorkDataWidget.hpp"
#include "widgets/schemeWidget.hpp"

namespace ble::gui::views::models {

class ViewWidgetsDto {
public:
    ViewWidgetsDto() { }
    ~ViewWidgetsDto() { }

    std::shared_ptr<widgets::DataWidget> dataWidget;
    std::shared_ptr<widgets::ConditionsWidget> conditionsWidget;
    std::shared_ptr<widgets::SatSolverSettsWidget> satsolver_widget;
    std::shared_ptr<widgets::GridSettsWidget> gridsetts_widget;
    std::shared_ptr<widgets::ShockFrontSettsWidget> shockfront_widget;
    std::shared_ptr<widgets::DimlesParamsWidget> dimles_params_widget;
    std::shared_ptr<widgets::FluidParamsGraphWidget> fluidParamsWidget;
    std::shared_ptr<widgets::ResultDataWidget> resultDataWidget;
    std::shared_ptr<widgets::WellWorkDataWidget> wellWorkDataWidget;
    std::shared_ptr<widgets::BoundVisualWidget> condWidget;
    std::shared_ptr<widgets::TauVisualWidget> tauWidget;
    std::shared_ptr<widgets::FwVisualWidget> fwWidget;
    std::shared_ptr<widgets::SchemeWidget> schemeWidget;
};

}

#endif
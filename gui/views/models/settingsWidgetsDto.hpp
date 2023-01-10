#ifndef BLE_GUI_VIEWS_MODELS_SETTINGSWIDGETSDTO_H_
#define BLE_GUI_VIEWS_MODELS_SETTINGSWIDGETSDTO_H_

#include <iostream>
#include <memory>

#include "conditionsWidget.hpp"
#include "dataWidget.hpp"
#include "dimlesParamsWidget.hpp"
#include "gridSettsWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"

namespace ble::gui::views::models {

class SettingsWidgetsDto {
public:
    SettingsWidgetsDto() { }
    ~SettingsWidgetsDto() { }

    std::shared_ptr<widgets::DataWidget> dataWidget;
    std::shared_ptr<widgets::ConditionsWidget> conditionsWidget;
    std::shared_ptr<widgets::SatSolverSettsWidget> satsolver_widget;
    std::shared_ptr<widgets::GridSettsWidget> gridsetts_widget;
    std::shared_ptr<widgets::ShockFrontSettsWidget> shockfront_widget;
    std::shared_ptr<widgets::DimlesParamsWidget> dimles_params_widget;
};

}

#endif
#ifndef BLE_GUI_WIDGETS_MODELS_DATAWIDGETCOMPONENTDTO_H_
#define BLE_GUI_WIDGETS_MODELS_DATAWIDGETCOMPONENTDTO_H_

#include <iostream>
#include <memory>

#include "gridSettsWidget.hpp"
#include "modelDataWidget.hpp"
#include "relPermDataWidget.hpp"
// #include "satSolverSettsWidget.hpp"
// #include "shockFrontSettsWidget.hpp"
// #include "conditionsWidget.hpp"
#include "geomDataWidget.hpp"
#include "geologyDataWidget.hpp"

namespace ble::gui::widgets::models {

struct DataComponents {
    // std::shared_ptr<GridSettsWidget> gridset_widget;
    std::shared_ptr<ModelDataWidget> modeldata_widget;
    std::shared_ptr<RelPermDataWidget> relperm_widget;
    // std::shared_ptr<SatSolverSettsWidget> satsolverset_view;
    // std::shared_ptr<ShockFrontSettsWidget> shockfront_widget;
    // std::shared_ptr<ConditionsWidget> cond_widget;
    std::shared_ptr<GeomDataWidget> geom_widget;
    std::shared_ptr<GeologyDataWidget> geol_widget;
};

}

#endif
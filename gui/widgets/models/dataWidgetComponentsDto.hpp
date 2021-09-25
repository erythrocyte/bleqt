#ifndef BLE_GUI_WIDGETS_MODELS_DATAWIDGETCOMPONENTDTO_H_
#define BLE_GUI_WIDGETS_MODELS_DATAWIDGETCOMPONENTDTO_H_

#include <iostream>
#include <memory>

#include "gridSettsWidget.hpp"
#include "modelDataWidget.hpp"
#include "relPermDataWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"
#include "boundaryConditionsWidget.hpp"

namespace ble::gui::widgets::models {

struct DataWidgetComponentsDto {
    std::shared_ptr<GridSettsWidget> gridset_widget;
    std::shared_ptr<ModelDataWidget> modeldata_widget;
    std::shared_ptr<RelPermDataWidget> relperm_widget;
    std::shared_ptr<SatSolverSettsWidget> satsolverset_view;
    std::shared_ptr<ShockFrontSettsWidget> shockfront_widget;
    std::shared_ptr<BoundaryConditionsWidget> boundarycond_widget;
};

}

#endif
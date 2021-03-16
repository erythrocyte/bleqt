#ifndef BLEGUI_WIDGETS_MODELS_DATAWIDGETCOMPONENTDTO_H_
#define BLEGUI_WIDGETS_MODELS_DATAWIDGETCOMPONENTDTO_H_

#include <iostream>
#include <memory>

#include "gridSettsWidget.hpp"
#include "modelDataWidget.hpp"

namespace ble_gui::widgets::models {

struct DataWidgetComponentsDto {
    std::shared_ptr<GridSettsWidget> gridset_view;
    std::shared_ptr<ModelDataWidget> modeldata_view;
};

}

#endif
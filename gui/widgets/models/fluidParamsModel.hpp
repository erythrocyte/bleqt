#ifndef BLEGUI_WIDGETS_MODELS_FLUIDPARAMSMODEL_H_
#define BLEGUI_WIDGETS_MODELS_FLUIDPARAMSMODEL_H_

#include <iostream>

namespace ble_gui {
namespace widgets {
    namespace models {
        struct FluidParamsModel {
            double max_dfbl;
            QList<QPointF> kws;
            QList<QPointF> koils;
            QList<QPointF> fbls;
            QList<QPointF> dfbls;
            QList<QPointF> scs;
        };
    }
}
}

#endif
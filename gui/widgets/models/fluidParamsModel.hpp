#ifndef BLEGUI_WIDGETS_MODELS_FLUIDPARAMSMODEL_H_
#define BLEGUI_WIDGETS_MODELS_FLUIDPARAMSMODEL_H_

#include <iostream>

#include <QList>

namespace ble_gui::widgets::models {

struct FluidParamsModel {
    double max_dfbl;
    QList<QPointF> kws;
    QList<QPointF> koils;
    QList<QPointF> fbls;
    QList<QPointF> dfbls;
    QList<QPointF> scs;
};

}

#endif
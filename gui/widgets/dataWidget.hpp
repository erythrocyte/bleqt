#ifndef BLEGUI_WIDGETS_DATAWIDGET_H_
#define BLEGUI_WIDGETS_DATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "gridSettsWidget.hpp"
#include "modelDataWidget.hpp"
#include "physicDataWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"

namespace ble_gui::widgets {
class DataWidget : public QWidget {
    Q_OBJECT

public:
    DataWidget(QWidget* parent = nullptr);
    ~DataWidget() { }

    // void set_view_objects(std::shared_ptr<ModelDataWidget> modelData);

    ModelDataWidget* ModelData;
    PhysDataWidget* PhysData;
    SaturSolverSettsWidget* SaturSolverSetts;
    GridSettsWidget* GridSetts;
    ShockFrontSettsWidget* ShockFrontSetts;

private:
    // std::shared_ptr<ModelDataWidget> _modelDataWidget;
};

} // namespace ble_gui::widgets

#endif

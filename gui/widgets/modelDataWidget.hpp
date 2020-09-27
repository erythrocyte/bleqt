#ifndef BLEGUI_WIDGETS_MODELDATAWIDGET_H_
#define BLEGUI_WIDGETS_MODELDATAWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_modelDataWidget.hpp"

namespace ble_gui {
namespace widgets {
    class ModelDataWidget : public QWidget, private UI::ModelData {
        Q_OBJECT
    public:
        ModelDataWidget(QWidget* parent = nullptr);
        ~ModelDataWidget() { delete ui; }

        double getModelingPeriod() const;

    private:
        UI::ModelData* ui;
    };
} // namespace widgets
} // namespace ble_gui

#endif

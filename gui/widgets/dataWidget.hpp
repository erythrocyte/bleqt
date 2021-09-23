#ifndef BLE_GUI_WIDGETS_DATAWIDGET_H_
#define BLE_GUI_WIDGETS_DATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "models/dataWidgetComponentsDto.hpp"
#include "modelDataWidget.hpp"
#include "relPermDataWidget.hpp"
#include "satSolverSettsWidget.hpp"
#include "shockFrontSettsWidget.hpp"

namespace ble::gui::widgets {
class DataWidget : public QWidget {
    Q_OBJECT

public:
    DataWidget(QWidget* parent = nullptr);
    ~DataWidget() { }

    void set_view_objects(std::shared_ptr<models::DataWidgetComponentsDto> components);
};

} // namespace ble_gui::widgets

#endif

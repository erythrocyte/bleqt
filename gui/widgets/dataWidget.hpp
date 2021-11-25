#ifndef BLE_GUI_WIDGETS_DATAWIDGET_H_
#define BLE_GUI_WIDGETS_DATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "common/models/data.hpp"
#include "models/dataComponents.hpp"
#include "uis/ui_dataWidget.hpp"

namespace ble::gui::widgets {
class DataWidget : public QWidget, private UI::Data {
    Q_OBJECT

public:
    DataWidget(QWidget* parent = nullptr);
    ~DataWidget();

    std::shared_ptr<ble::src::common::models::Data> get_data();
    // void set_view_objects(std::shared_ptr<models::DataComponents> components);

signals:
    void rp_values_updated();

private:
    UI::Data* ui;

    void subscribe();

private slots:
    void rp_values_changed() { emit rp_values_updated(); }
};

} // namespace ble_gui::widgets

#endif

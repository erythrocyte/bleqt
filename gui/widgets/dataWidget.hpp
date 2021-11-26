#ifndef BLE_GUI_WIDGETS_DATAWIDGET_H_
#define BLE_GUI_WIDGETS_DATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "common/models/data.hpp"
#include "uis/ui_dataWidget.hpp"

namespace ble::gui::widgets {
class DataWidget : public QWidget, private UI::Data {
    Q_OBJECT

public:
    DataWidget(QWidget* parent = nullptr);
    ~DataWidget();

    std::shared_ptr<ble::src::common::models::Data> get_data();

signals:
    void rp_values_updated();

private:
    UI::Data* ui;

    void subscribe();

private slots:
    void rp_values_changed() { emit rp_values_updated(); }
    void use_fw_limit_toogled(bool state);
};

} // namespace ble_gui::widgets

#endif

#ifndef BLE_GUI_WIDGETS_GEOLOGYDATAWIDGET_H_
#define BLE_GUI_WIDGETS_GEOLOGYDATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "uis/ui_geologyDataWidget.hpp"


namespace ble::gui::widgets {

class GeologyDataWidget : public QWidget, private UI::GeologyData {
    Q_OBJECT
public:
    GeologyDataWidget(QWidget* parent = nullptr);
    ~GeologyDataWidget() { delete ui; }

    double get_k() const { return ui->Perm->value(); }
    double get_kf() const {return ui->PermFract->value();}
    double get_mf() const {return ui->PoroFract->value();}

private:
    UI::GeologyData* ui;

    void subscribe();
};

} // namespace ble_gui::widgets

#endif
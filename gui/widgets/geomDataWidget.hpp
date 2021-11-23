#ifndef BLE_GUI_WIDGETS_GEOMDATAWIDGET_H_
#define BLE_GUI_WIDGETS_GEOMDATAWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "uis/ui_geomDataWidget.hpp"


namespace ble::gui::widgets {

class GeomDataWidget : public QWidget, private UI::GeomData {
    Q_OBJECT
public:
    GeomDataWidget(QWidget* parent = nullptr);
    ~GeomDataWidget() { delete ui; }

    double get_rw() const { return ui->Rw->value(); }
    double get_r() const {return ui->R->value();}
    double get_l() const {return ui->L->value();}
    double get_delta() const {return ui->Delta->value();}

private:
    UI::GeomData* ui;

    void subscribe();
    void fix_well_radius(const QString&);
};

} // namespace ble_gui::widgets

#endif
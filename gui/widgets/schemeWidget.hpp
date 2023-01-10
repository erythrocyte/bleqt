#ifndef BLE_GUI_WIDGETS_SCHEMEWIDGET_H_
#define BLE_GUI_WIDGETS_SCHEMEWIDGET_H_

#include "uis/ui_schemeWidget.hpp"

namespace ble::gui::widgets {

class SchemeWidget : public QWidget, private UI::Scheme {
    Q_OBJECT
public:
    SchemeWidget(QWidget* parent = nullptr);
    ~SchemeWidget() { delete ui; }

private:
    UI::Scheme* ui;

    void subscribe();
};

} // namespace ble_gui::widgets

#endif

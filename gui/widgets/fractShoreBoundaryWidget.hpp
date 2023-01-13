#ifndef BLE_GUI_WIDGETS_FRACTSHOREBOUNDARYWIDGET_H_
#define BLE_GUI_WIDGETS_FRACTSHOREBOUNDARYWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_fractShoreBoundaryWidget.hpp"

namespace ble::gui::widgets {

class FractShoreWidget : public QWidget, private UI::FractShore {
    Q_OBJECT
public:
    FractShoreWidget(QWidget* parent = nullptr);
    ~FractShoreWidget() { delete ui; }

private:
    UI::FractShore* ui;

    void subscribe();
};

}

#endif
#ifndef BLE_GUI_WIDGETS_FRACTSHOREBOUNDARYWIDGET_H_
#define BLE_GUI_WIDGETS_FRACTSHOREBOUNDARYWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_fractShoreBoundaryWidget.hpp"

namespace ble::gui::widgets {

class FractShoreWidget : public QWidget, public UI::FractShore {
    Q_OBJECT
public:
    FractShoreWidget(QWidget* parent = nullptr);
    ~FractShoreWidget() { delete ui; }

    UI::FractShore* ui;

private:
    void subscribe();
};

}

#endif
#ifndef BLE_GUI_GRIDSETTSWIDGET_H_
#define BLE_GUI_GRIDSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

namespace ble_gui
{
    class GridSettsWidget : public QWidget
    {
        Q_OBJECT
    public:
        GridSettsWidget(QWidget *parent = nullptr);
        ~GridSettsWidget() {}

        QDoubleSpinBox *Length;
        QSpinBox *CellCount;
        QComboBox *GridType;
    };

} // namespace ble_gui

#endif
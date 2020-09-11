#ifndef BLE_GUI_SATSOLVERSETTSWIDGET_H_
#define BLE_GUI_SATSOLVERSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

namespace ble_gui
{
    class SaturSolverSettsWidget : public QWidget
    {
        Q_OBJECT
    public:
        SaturSolverSettsWidget(QWidget *parent = nullptr);
        ~SaturSolverSettsWidget() {}

        QDoubleSpinBox *Curant;
        QSpinBox *RecalcPressN;
        QComboBox *SolverType;
    };

} // namespace ble_gui

#endif
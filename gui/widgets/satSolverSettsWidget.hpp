#ifndef BLEGUI_WIDGETS_SATSOLVERSETTSWIDGET_H_
#define BLEGUI_WIDGETS_SATSOLVERSETTSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

namespace ble_gui
{
    namespace widgets
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
    } // namespace widgets
} // namespace ble_gui

#endif
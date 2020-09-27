#ifndef BLEGUI_WIDGETS_PHYSICDATAWIDGET_H_
#define BLEGUI_WIDGETS_PHYSICDATAWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_physicDataWidget.hpp"

namespace ble_gui {
namespace widgets {
    class PhysDataWidget : public QWidget, private UI::PhysicData {
        Q_OBJECT
    public:
        PhysDataWidget(QWidget* parent = nullptr);
        ~PhysDataWidget() { delete ui; }

        double getKmu() const { return ui->Kmu->value(); }
        double getNwat() const { return ui->Nwat->value(); }
        double getNoil() const { return ui->Noil->value(); }

    signals:
        void valuesUpdated();

    private:
        UI::PhysicData* ui;

        void addQDoubleSpinBoxLabel(QDoubleSpinBox* widget,
            double min, double max, double step, double value, int decimals,
            int spinboxRow, int spinboxCol, QLabel* label, int labelRow, int labelCol);

    private slots:
        void changeValues() { emit valuesUpdated(); }
    };
} // namespace widgets
} // namespace ble_gui

#endif

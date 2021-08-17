#ifndef BLEGUI_WIDGETS_RELPERMDATAWIDGET_H_
#define BLEGUI_WIDGETS_RELPERMDATAWIDGET_H_

#include <iostream>
#include <memory>

#include "uis/ui_relPermDataWidget.hpp"

namespace ble_gui::widgets {
class RelPermDataWidget : public QWidget, private UI::RelPermData {
    Q_OBJECT
public:
    RelPermDataWidget(QWidget* parent = nullptr);
    ~RelPermDataWidget() { delete ui; }

    double getKmu() const { return ui->Kmu->value(); }
    double getN() const { return ui->N->value(); }

signals:
    void valuesUpdated();

private:
    UI::RelPermData* ui;

    void addQDoubleSpinBoxLabel(QDoubleSpinBox* widget,
        double min, double max, double step, double value, int decimals,
        int spinboxRow, int spinboxCol, QLabel* label, int labelRow, int labelCol);

private slots:
    void changeValues() { emit valuesUpdated(); }
};

} // namespace ble_gui::widgets

#endif

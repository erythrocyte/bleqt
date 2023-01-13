#ifndef BLE_GUI_WIDGETS_CONDITIONSWIDGET_H_
#define BLE_GUI_WIDGETS_CONDITIONSWIDGET_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "common/models/boundCondData.hpp"
#include "uis/ui_conditionsWidget.hpp"

namespace ble::gui::widgets {

class ConditionsWidget : public QWidget, private UI::Conditions {
    Q_OBJECT
public:
    ConditionsWidget(QWidget* parent = nullptr);
    ~ConditionsWidget() { delete ui; }

    std::shared_ptr<src::common::models::BoundCondData> get_bound_data(double x0, double x1);

signals:
    void rhs_updated();
    void init_updated();

private:
    UI::Conditions* ui;

    void set_items();
    void subscribe();
    QString get_choosed_file();

private slots:

    void initSaturTypeChanged(const QString& value);
    void initSaturFileChosen(bool checked);
    void initSatConstChanged(double value);

    void impermChecked(bool checked);
    void boundSaturTypeChanged(const QString& value);
    void boundSaturFileChosen(bool checked);
    void boundSaturConstChanged(double value);
    void qTypeChanged(const QString& value);
    void qFileChosen(bool checked);
    void qConstChanged(double value);
    void useQChecked(bool checked);
    void fractEndImperChecked(bool state);
};

} // namespace ble_gui::widgets

#endif
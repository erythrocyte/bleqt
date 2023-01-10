#include "schemeWidget.hpp"

#include <iostream>

namespace ble::gui::widgets {

// class SchemeWidget : public QWidget, private UI::Scheme {
//     Q_OBJECT
// public:
SchemeWidget::SchemeWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::Scheme)
{
    ui->setupUi(this);

    subscribe();
}

void SchemeWidget::subscribe()
{
}

} // namespace ble_gui::widgets

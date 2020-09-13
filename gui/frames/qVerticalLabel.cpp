#include "qVerticalLabel.hpp"

#include <QPainter>

ble_gui::frames::QVerticalLabel::QVerticalLabel(QWidget *parent)
    : QLabel(parent)
{
}

ble_gui::frames::QVerticalLabel::QVerticalLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
}

void ble_gui::frames::QVerticalLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(_textColor);
    painter.setBrush(Qt::Dense1Pattern);

    painter.translate(sizeHint().width(), sizeHint().height());
    painter.rotate(270);

    painter.drawText(0, 0, text());
}

QSize ble_gui::frames::QVerticalLabel::minimumSizeHint() const
{
    QSize s = QLabel::minimumSizeHint();
    return QSize(s.height(), s.width());
}

QSize ble_gui::frames::QVerticalLabel::sizeHint() const
{
    QSize s = QLabel::sizeHint();
    return QSize(s.height(), s.width());
}

void ble_gui::frames::QVerticalLabel::setTextColor(QColor color) 
{
    _textColor = color;
}
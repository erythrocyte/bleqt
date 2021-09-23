#include "qVerticalLabel.hpp"

#include <QPainter>

namespace ble::gui::frames {
QVerticalLabel::QVerticalLabel(QWidget* parent)
    : QLabel(parent)
{
}

QVerticalLabel::QVerticalLabel(const QString& text, QWidget* parent)
    : QLabel(text, parent)
{
}

void QVerticalLabel::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(_textColor);
    painter.setBrush(Qt::Dense1Pattern);

    painter.translate(sizeHint().width(), sizeHint().height());
    painter.rotate(270);

    painter.drawText(0, 0, text());
}

QSize QVerticalLabel::minimumSizeHint() const
{
    QSize s = QLabel::minimumSizeHint();
    return QSize(s.height(), s.width());
}

QSize QVerticalLabel::sizeHint() const
{
    QSize s = QLabel::sizeHint();
    return QSize(s.height(), s.width());
}

void QVerticalLabel::setTextColor(QColor color)
{
    _textColor = color;
}

}
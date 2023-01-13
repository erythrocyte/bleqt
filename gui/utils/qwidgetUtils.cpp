#include "qwidgetUtils.hpp"

#include <QRegularExpression>

namespace ble::gui::utils {

QList<QWidget*> QWidgetUtils::getChildWidgets(QWidget* parent, const QString& search)
{
    if (search.isNull())
        parent->findChildren<QWidget*>();

    QRegularExpression exp(search);
    return parent->findChildren<QWidget*>(exp);
}

}

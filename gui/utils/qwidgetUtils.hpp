#ifndef BLE_GUI_UTILS_QWIDGETUTILS_H_
#define BLE_GUI_UTILS_QWIDGETUTILS_H_

#include <QList>
#include <QString>
#include <QWidget>

namespace ble::gui::utils {
class QWidgetUtils {
public:
    static QList<QWidget*> getChildWidgets(QWidget* parent, const QString& search = QString());

private:
    QWidgetUtils() { }
    ~QWidgetUtils() { }
};
}

#endif
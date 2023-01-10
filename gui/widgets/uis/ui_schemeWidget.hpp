#ifndef BLE_GUI_WIDGETS_UI_SCHEMEWIDGET_H_
#define BLE_GUI_WIDGETS_UI_SCHEMEWIDGET_H_

#include <iostream>

#include <QGridLayout>
#include <QSvgWidget>
#include <QToolBar>
#include <QWidget>

namespace ble::gui::widgets::UI {
class Scheme {
public:
    QSvgWidget* main_svg_widget;

    void setupUi(QWidget* widget)
    {
        QGridLayout* layout = new QGridLayout(widget);

        main_svg_widget = new QSvgWidget();
        layout->addWidget(main_svg_widget, 1, 0, 1, 1);

        _mainToolBar = new QToolBar(widget);
        layout->addWidget(_mainToolBar, 0, 0, 1, 1);

        widget->setLayout(layout);

        std::cout << "in setup ui\n";
    }

private:
    QToolBar* _mainToolBar;
};

}

#endif
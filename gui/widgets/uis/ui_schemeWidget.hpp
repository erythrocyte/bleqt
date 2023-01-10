#ifndef BLE_GUI_WIDGETS_UI_SCHEMEWIDGET_H_
#define BLE_GUI_WIDGETS_UI_SCHEMEWIDGET_H_

#include <iostream>

#include <QGridLayout>
#include <QSvgRenderer>
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

        render_svg_image();
    }

private:
    QToolBar* _mainToolBar;

    QSvgRenderer* m_svg_renderer;

    void render_svg_image()
    {
        QString file_path = ":/guirecources/scheme";
        m_svg_renderer = new QSvgRenderer(file_path);
    }
};

}

#endif
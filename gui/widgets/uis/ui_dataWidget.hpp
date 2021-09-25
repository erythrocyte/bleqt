#ifndef BLE_GUI_WIDGETS_UI_DATAWIDGET_H_
#define BLE_GUI_WIDGETS_UI_DATAWIDGET_H_

#include <iostream>

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

namespace ble::gui::widgets::UI {

class Data {

public:
    QVBoxLayout* MainLayout;

    void setupUI(QWidget* widget)
    {
        MainLayout = new QVBoxLayout(widget);
        MainLayout->setMargin(0);
        MainLayout->setSpacing(0);
        MainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

        m_window = new QWidget(widget);
        m_window->setLayout(MainLayout);

        m_scrollArea = new QScrollArea(widget);
        m_scrollArea->setWidget(m_window);
        m_scrollArea->show();

        m_layout = new QVBoxLayout(widget);
        m_layout->addWidget(m_scrollArea);

        widget->setLayout(m_layout);
    }

private:
    QWidget* m_window;
    QScrollArea* m_scrollArea;
    QVBoxLayout* m_layout;
};

}

#endif
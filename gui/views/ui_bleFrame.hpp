#ifndef GUI_VIEWS_UIBLEFRAME_H_
#define GUI_VIEWS_UIBLEFRAME_H_

#include <QChart>
#include <QChartView>
#include <QGridLayout>
#include <QLineSeries>
#include <QValueAxis>
#include <QWidget>

namespace ble_gui::views::UI {

class UI_BleFrame {
public:
    QWidget* central;
    void retranslateUi(QWidget* widget)
    {
    }

    void setupUI(QWidget* widget)
    {
        layout = new QGridLayout;

        central = new QWidget(widget);
        central->setLayout(layout);
    }

private:
    
    QGridLayout* layout;
    // QMenu* menu;
    // QStatusBar* statusBar;
    // QLabel* statusLabel;
    // QProgressBar* statusProgressBar;
    // QDockWidget* _dock;
};

}

#endif
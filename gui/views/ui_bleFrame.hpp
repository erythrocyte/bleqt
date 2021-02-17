#ifndef GUI_VIEWS_UIBLEFRAME_H_
#define GUI_VIEWS_UIBLEFRAME_H_

// #include <QChart>
// #include <QChartView>
#include <QGridLayout>
// #include <QLineSeries>
// #include <QValueAxis>
#include <QLabel>
#include <QStatusBar>
#include <QWidget>
#include <QProgressBar>

namespace ble_gui::views::UI {

class UI_BleFrame {
public:
    QWidget* central;
    QStatusBar* statusBar;

    void retranslateUi(QWidget* widget)
    {
        statusLabel->setText("Ready to run calculation");
    }

    void setupUI(QWidget* widget)
    {
        layout = new QGridLayout;

        central = new QWidget(widget);
        central->setLayout(layout);

        statusBar = new QStatusBar();
        statusLabel = new QLabel("Ready to run calculation");
        statusBar->addWidget(statusLabel);
        statusProgressBar = new QProgressBar();
        statusProgressBar->setMaximum(100);
        statusBar->addWidget(statusProgressBar);
    }

private:
    QGridLayout* layout;
    // QMenu* menu;
    QLabel* statusLabel;
    QProgressBar* statusProgressBar;
    // QDockWidget* _dock;
};

}

#endif
#ifndef GUI_VIEWS_UIBLEFRAME_H_
#define GUI_VIEWS_UIBLEFRAME_H_

#include <QCommonStyle>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPen>
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QStatusBar>
#include <QWidget>

namespace ble_gui::views::UI {

class UI_BleFrame {
public:
    QWidget* central;
    QStatusBar* statusBar;
    QAction* quit;
    QAction* runAction;
    QMenuBar* menuBar;
    QDockWidget* dockSettings;
    QDockWidget* dockMessages;
    QPlainTextEdit* messagePlainText;
    QTabWidget* tabs;
    QProgressBar* statusProgressBar;
    QLabel* statusLabel;

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

        setupStatusBar(widget);
        setupDock(widget);
        setupMenu(widget);

        tabs = new QTabWidget(widget);
        layout->addWidget(tabs, 0, 0);
    }

private:
    QGridLayout* layout;
    QMenu* menu;

    void setupStatusBar(QWidget* widget)
    {
        statusBar = new QStatusBar();
        statusLabel = new QLabel("Ready to run calculation");
        statusBar->addWidget(statusLabel);
        statusProgressBar = new QProgressBar();
        statusProgressBar->setMaximum(100);
        statusBar->addWidget(statusProgressBar);
    }

    void setupDock(QWidget* widget)
    {
        dockSettings = new QDockWidget("Settings", widget);
        dockMessages = new QDockWidget("Messages", widget);

        messagePlainText = new QPlainTextEdit(widget);
        messagePlainText->setReadOnly(true);
        dockMessages->setWidget(messagePlainText);
    }

    void setupMenu(QWidget* widget)
    {
        menuBar = new QMenuBar(widget);

        QCommonStyle* style = new QCommonStyle();
        quit = new QAction("&Quit", widget);
        quit->setIcon(style->standardIcon(QStyle::SP_DialogCloseButton));

        QMenu* file = menuBar->addMenu("&File");
        file->addAction(quit);

        menu = menuBar->addMenu("&View");
        QAction* showSettings = dockSettings->toggleViewAction();
        showSettings->setIcon(style->standardIcon(QStyle::SP_FileDialogDetailedView));
        menu->addAction(showSettings);

        QAction* showMessages = dockMessages->toggleViewAction();
        showMessages->setIcon(style->standardIcon(QStyle::SP_DesktopIcon));
        menu->addAction(showMessages);

        menu = menuBar->addMenu("&Task");
        runAction = new QAction("Run");
        runAction->setIcon(style->standardIcon(QStyle::SP_MediaPlay));
        menu->addAction(runAction);
    }
};

}

#endif

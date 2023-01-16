#ifndef BLE_GUI_WIDGETS_UI_DATAVISUAL_H_
#define BLE_GUI_WIDGETS_UI_DATAVISUAL_H_

#include <functional>
#include <iostream>
#include <memory>

#include <QAction>
#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QCommonStyle>
#include <QFont>
#include <QGridLayout>
#include <QLabel>
#include <QLineSeries>
#include <QSlider>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QValueAxis>

using namespace QtCharts;

namespace ble::gui::widgets::UI {
class ResultData {
public:
    QChart* Chart;
    QLineSeries* SeriesPress;
    QLineSeries* SeriesPressAn;
    QLineSeries* SeriesSatNum;
    QLineSeries* SeriesSatAn;
    QLineSeries* SeriesSc;
    QSlider* Slider;
    QLabel* Label;
    QAction* BtnSeekBack;
    QAction* BtnStepBack;
    QAction* BtnPlayPause;
    QAction* BtnStop;
    QAction* BtnStepForward;
    QAction* BtnSeekForward;
    QTimer* Timer;
    QToolButton* TlBtnSpeed;
    QAction* SpeedLowQuarter;
    QAction* SpeedLowHalf;
    QAction* SpeedLowHalfQuarter;
    QAction* SpeedNormal;
    QAction* SpeedHighQuarter;
    QAction* SpeedHighHalf;
    QAction* SpeedHighTwice;
    QCheckBox* press_global_limit;
    QCheckBox* LoopAnimation;

    QAction* action_save;

    void setupUi(QWidget* widget)
    {
        Timer = new QTimer(widget);

        _layout = new QGridLayout(widget);

        prepareMainToolbarUp(widget);
        _layout->addWidget(m_toolbar_up, 0, 0, 1, 11);

        press_global_limit = new QCheckBox("Global limit for press", widget);
        press_global_limit->setChecked(true);
        _layout->addWidget(press_global_limit, 3, 0, 1, 1);

        LoopAnimation = new QCheckBox("Loop animation", widget);
        LoopAnimation->setChecked(false);
        _layout->addWidget(LoopAnimation, 3, 1, 1, 1);

        QCommonStyle* style = new QCommonStyle();
        m_toolbar_play_buttons = new QToolBar(widget);
        BtnSeekBack = new QAction("&Seek Back", widget);
        BtnSeekBack->setIcon(style->standardIcon(QStyle::SP_MediaSkipBackward));
        m_toolbar_play_buttons->addAction(BtnSeekBack);
        BtnStepBack = new QAction("&Step Back", widget);
        BtnStepBack->setIcon(style->standardIcon(QStyle::SP_MediaSeekBackward));
        m_toolbar_play_buttons->addAction(BtnStepBack);
        BtnPlayPause = new QAction("&Play", widget);
        BtnPlayPause->setIcon(style->standardIcon(QStyle::SP_MediaPlay));
        m_toolbar_play_buttons->addAction(BtnPlayPause);
        BtnStop = new QAction("&Stop", widget);
        BtnStop->setIcon(style->standardIcon(QStyle::SP_MediaStop));
        m_toolbar_play_buttons->addAction(BtnStop);
        BtnStepForward = new QAction("&Step Forward", widget);
        BtnStepForward->setIcon(style->standardIcon(QStyle::SP_MediaSeekForward));
        m_toolbar_play_buttons->addAction(BtnStepForward);
        BtnSeekForward = new QAction("&Seek Forward", widget);
        BtnSeekForward->setIcon(style->standardIcon(QStyle::SP_MediaSkipForward));
        m_toolbar_play_buttons->addAction(BtnSeekForward);

        QAction* speedAction = new QAction("&Speed", widget);
        speedAction->setIcon(style->standardIcon(QStyle::SP_DesktopIcon));
        m_toolbar_play_buttons->addAction(speedAction);
        TlBtnSpeed = dynamic_cast<QToolButton*>(m_toolbar_play_buttons->widgetForAction(speedAction));
        TlBtnSpeed->setPopupMode(QToolButton::InstantPopup);
        TlBtnSpeed->addAction(SpeedLowQuarter = new QAction("0.25", widget));
        TlBtnSpeed->addAction(SpeedLowHalf = new QAction("0.5", widget));
        TlBtnSpeed->addAction(SpeedLowHalfQuarter = new QAction("0.75", widget));
        TlBtnSpeed->addAction(SpeedNormal = new QAction("Normal", widget));
        TlBtnSpeed->addAction(SpeedHighQuarter = new QAction("1.25", widget));
        TlBtnSpeed->addAction(SpeedHighHalf = new QAction("1.5", widget));
        TlBtnSpeed->addAction(SpeedHighTwice = new QAction("2.0", widget));
        TlBtnSpeed->removeAction(speedAction);

        m_currentSpeed = SpeedNormal;
        update_selected_speed(m_currentSpeed);

        _layout->addWidget(m_toolbar_play_buttons, 2, 0, 1, 3);

        Slider = new QSlider(Qt::Orientation::Horizontal);
        _layout->addWidget(Slider, 2, 3, 1, 7);
        Slider->setTickInterval(1.);
        Slider->setMinimum(1);
        Slider->setMaximum(1);
        Slider->setValue(1);

        Label = new QLabel();
        _layout->addWidget(Label, 2, 10);

        Chart = new QChart();
        Chart->legend()->setVisible(true);

        // Настройка осей графика
        _axisX = new QValueAxis();
        _axisX->setLabelFormat("%g");
        _axisX->setTickCount(5);
        _axisX->setRange(0., 1.);

        _axisYSat = new QValueAxis();
        _axisYSat->setLabelFormat("%g");
        _axisYSat->setTickCount(5);
        _axisYSat->setRange(0., 1.);

        _axisYPress = new QValueAxis();
        _axisYPress->setLabelFormat("%g");
        _axisYPress->setTickCount(5);
        _axisYPress->setRange(0., 1.);

        _chartView = new QChartView(Chart);
        _layout->addWidget(_chartView, 1, 0, 1, 11);

        SeriesPress = new QLineSeries();
        SeriesPressAn = new QLineSeries();
        SeriesSatNum = new QLineSeries();
        SeriesSatAn = new QLineSeries();

        Chart->addSeries(SeriesPress);
        Chart->addSeries(SeriesPressAn);
        Chart->addSeries(SeriesSatNum);
        Chart->addSeries(SeriesSatAn);

        Chart->addAxis(_axisX, Qt::AlignBottom);
        Chart->addAxis(_axisYPress, Qt::AlignLeft);
        Chart->addAxis(_axisYSat, Qt::AlignRight);

        SeriesSc = new QLineSeries();
        _pen.setStyle(Qt::DotLine);
        _pen.setWidth(2);
        // pen.setBrush(Qt::green);
        SeriesSc->setPen(_pen);
        Chart->addSeries(SeriesSc);

        SeriesPress->attachAxis(_axisX);
        SeriesPress->attachAxis(_axisYPress);

        SeriesPressAn->attachAxis(_axisX);
        SeriesPressAn->attachAxis(_axisYPress);

        SeriesSatAn->attachAxis(_axisX);
        SeriesSatAn->attachAxis(_axisYSat);

        SeriesSatNum->attachAxis(_axisX);
        SeriesSatNum->attachAxis(_axisYSat);

        SeriesSc->attachAxis(_axisX);
        SeriesSc->attachAxis(_axisYSat);

        retranslateUi();
    }

    void set_press_axis_range(double min, double max)
    {
        _axisYPress->setRange(min, max);
    }

    void retranslateUi()
    {
        _axisX->setTitleText("x/r");
        _axisYSat->setTitleText("s");
        _axisYPress->setTitleText("p");
        SeriesPress->setName("p");
        SeriesPressAn->setName("p_an");
        SeriesSatNum->setName("s_num");
        SeriesSatAn->setName("s_an");
        SeriesSc->setName("sc");
    }

    void set_play_icon(bool playing)
    {
        QCommonStyle* style = new QCommonStyle();
        if (playing) {
            BtnPlayPause->setIcon(style->standardIcon(QStyle::SP_MediaPause));
        } else {
            BtnPlayPause->setIcon(style->standardIcon(QStyle::SP_MediaPlay));
        }
    }

    void tool_bar_enabled(bool status)
    {
        m_toolbar_play_buttons->setEnabled(status);
    }

    double update_selected_speed(QObject* sender)
    {
        QFont font;
        font = m_currentSpeed->font();
        font.setBold(false);
        m_currentSpeed->setFont(font);

        m_currentSpeed = qobject_cast<QAction*>(sender);
        Q_ASSERT(m_currentSpeed);

        font = m_currentSpeed->font();
        font.setBold(true);
        m_currentSpeed->setFont(font);

        return get_current_speed();
    }

    double get_current_speed()
    {
        return get_speed(m_currentSpeed);
    }

private:
    QGridLayout* _layout;
    QPen _pen;
    QChartView* _chartView;
    QValueAxis* _axisX;
    QValueAxis* _axisYPress;
    QValueAxis* _axisYSat;
    QToolBar* m_toolbar_play_buttons;
    QToolBar* m_toolbar_up;
    QAction* m_currentSpeed;

    double get_speed(QAction* action)
    {
        double norm_speed = 1; // ms;
        double cf = 1.0;
        if (action == SpeedLowQuarter)
            cf = 0.01;
        else if (action == SpeedLowHalf)
            cf = 0.1;
        else if (action == SpeedLowHalfQuarter)
            cf = 0.5;
        else if (action == SpeedNormal)
            cf = 1.0;
        else if (action == SpeedHighQuarter)
            cf = 2;
        else if (action == SpeedHighHalf)
            cf = 10;
        else if (action == SpeedHighTwice)
            cf = 100;

        return norm_speed * (1.0 / cf);
    }

    void prepareMainToolbarUp(QWidget* widget)
    {
        m_toolbar_up = new QToolBar(widget);

        QCommonStyle* style = new QCommonStyle();

        action_save = new QAction("Save", widget);
        action_save->setIcon(style->standardIcon(QStyle::SP_DialogSaveButton));
        m_toolbar_up->addAction(action_save);
    }
};

}

#endif

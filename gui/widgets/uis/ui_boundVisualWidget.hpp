#ifndef BLE_GUI_WIDGETS_UI_BOUNDARYCONDRESULTWIDGET_H_
#define BLE_GUI_WIDGETS_UI_BOUNDARYCONDRESULTWIDGET_H_

#include <functional>
#include <iostream>
#include <memory>

#include <QBoxLayout>
#include <QChart>
#include <QChartView>
#include <QCommonStyle>
#include <QGridLayout>
#include <QLabel>
#include <QLineSeries>
#include <QSplitter>
#include <QTableView>
#include <QToolBar>
#include <QValueAxis>

using namespace QtCharts;

namespace ble::gui::widgets::UI {

class BoundVisual {
public:
    QChart* Chart;
    QAction* ShowTable;
    QTableView* Table;

    void setupUi(QWidget* widget)
    {
        add_toolbar(widget);
        add_chartview();
        add_tableview();
        add_splitter();

        _chartTableLayout = new QGridLayout();
        _chartTableLayout->addWidget(_splitter, 0, 0, 1, 11);
        _toolLayout->addLayout(_chartTableLayout);

        retranslateUi();
    }

    void retranslateUi()
    {
        _axisX->setTitleText("l");
        _axisY->setTitleText("rhs");
    }

    void setup_xaxis_max(double value)
    {
        _axisX->setRange(0.0, value);
    }

    void add_series(QLineSeries* series)
    {
        Chart->addSeries(series);

        series->attachAxis(_axisX);
        series->attachAxis(_axisY);
    }

    QLineSeries* create_series(QString name)
    {
        auto result = new QLineSeries();
        result->setName(name);
        return result;
    }

    void setup_yaxis_range(double minVal, double maxVal)
    {
        _axisY->setRange(minVal, maxVal);
    }

private:
    QGridLayout* _chartTableLayout;
    QChartView* _chartView;
    QValueAxis* _axisX;
    QValueAxis* _axisY;
    QToolBar* _toolbar;
    QSplitter* _splitter;
    QBoxLayout* _toolLayout;

    void add_chartview()
    {
        Chart = new QChart();
        Chart->legend()->setVisible(true);

        // Настройка осей графика
        _axisX = new QValueAxis();
        _axisX->setLabelFormat("%g");
        _axisX->setTickCount(5);
        _axisX->setMin(0.0);

        _axisY = new QValueAxis();
        _axisY->setLabelFormat("%g");
        _axisY->setTickCount(5);
        _axisY->setMin(0.0);

        Chart->addAxis(_axisX, Qt::AlignBottom);
        Chart->addAxis(_axisY, Qt::AlignLeft);

        _chartView = new QChartView(Chart);
    }

    void add_tableview()
    {
        Table = new QTableView();
        Table->hide();
    }

    void add_splitter()
    {
        _splitter = new QSplitter();
        _splitter->addWidget(_chartView);
        _splitter->addWidget(Table);
        _splitter->setOrientation(Qt::Orientation::Vertical);
        _splitter->setStretchFactor(0, 4);
        _splitter->setStretchFactor(1, 1);
    }

    void add_toolbar(QWidget* widget)
    {
        _toolLayout = new QBoxLayout(QBoxLayout::TopToBottom, widget);
        //set margins to zero so the toolbar touches the widget's edges
        _toolLayout->setContentsMargins(0, 0, 0, 0);

        QCommonStyle* style = new QCommonStyle();
        _toolbar = new QToolBar(widget);
        ShowTable = new QAction("&Show Table", widget);
        ShowTable->setIcon(style->standardIcon(QStyle::SP_FileDialogListView));
        _toolbar->addAction(ShowTable);
        _toolLayout->addWidget(_toolbar);
    }
};

}

#endif

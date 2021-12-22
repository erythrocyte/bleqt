#ifndef BLE_GUI_WIDGETS_UI_FWVISUALWIDGET_H_
#define BLE_GUI_WIDGETS_UI_FWVISUALWIDGET_H_

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

class FwVisual {
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
        _axis_x->setTitleText("PV");
        _axis_y_s->setTitleText("s");
        _axis_y_fw->setTitleText("fw");
    }

    void setup_xaxis_max(double value)
    {
        _axis_x->setRange(0.0, value);
    }

    void add_series(QLineSeries* series, int k)
    {
        Chart->addSeries(series);
        series->attachAxis(_axis_x);
        series->attachAxis(get_y_axis(k));
    }

    QLineSeries* create_series(QString name)
    {
        auto result = new QLineSeries();
        result->setName(name);
        return result;
    }

    void setup_yaxis_range(double minVal, double maxVal, int k)
    {
        auto yaxis = get_y_axis(k);
        yaxis->setRange(minVal, maxVal);
    }

    QValueAxis* get_y_axis(int k)
    {
        switch (k) {
        case 1:
        case 2:
            return _axis_y_fw;
        default:
            return _axis_y_s;
        }
    }

private:
    QGridLayout* _chartTableLayout;
    QChartView* _chartView;
    QValueAxis* _axis_x;
    QValueAxis* _axis_y_s;
    QValueAxis* _axis_y_fw;
    QToolBar* _toolbar;
    QSplitter* _splitter;
    QBoxLayout* _toolLayout;

    void add_chartview()
    {
        Chart = new QChart();
        Chart->legend()->setVisible(true);

        // Настройка осей графика
        _axis_x = new QValueAxis();
        _axis_x->setLabelFormat("%g");
        _axis_x->setTickCount(5);
        _axis_x->setMin(0.0);

        _axis_y_s = new QValueAxis();
        _axis_y_s->setLabelFormat("%g");
        _axis_y_s->setTickCount(5);
        _axis_y_s->setMin(0.0);

        _axis_y_fw = new QValueAxis();
        _axis_y_fw->setLabelFormat("%g");
        _axis_y_fw->setTickCount(5);
        _axis_y_fw->setMin(0.0);

        Chart->addAxis(_axis_x, Qt::AlignBottom);
        Chart->addAxis(_axis_y_fw, Qt::AlignLeft);
        Chart->addAxis(_axis_y_s, Qt::AlignRight);

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
        // set margins to zero so the toolbar touches the widget's edges
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

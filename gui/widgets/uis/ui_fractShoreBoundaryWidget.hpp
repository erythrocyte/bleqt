#ifndef BLE_GUI_WIDGETS_UIS_UIFRACTSHOREBOUNDARYWIDGET_H_
#define BLE_GUI_WIDGETS_UIS_UIFRACTSHOREBOUNDARYWIDGET_H_

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QWidget>

namespace ble::gui::widgets::UI {

class FractShore {
public:
    QCheckBox* cb_impermeable;
    QDoubleSpinBox* qdsb_press_value;

    void setupUi(QWidget* parent)
    {
        auto main_layout = new QGridLayout(parent);
        main_layout->setContentsMargins(0, 0, 0, 0);
        parent->setLayout(main_layout);

        auto gb = new QGroupBox("Fract shores", parent);
        auto gl = new QGridLayout(gb);
        gb->setLayout(gl);
        main_layout->addWidget(gb);

        setupGbSatur(gb);
        setupGbFlow(gb);

        cb_impermeable = new QCheckBox("Impermeable", gb);
        cb_impermeable->setChecked(false);
        gl->addWidget(cb_impermeable, 0, 0, 1, 4);

        gl->addWidget(m_gb_satur, 1, 0, 1, 4);
        gl->addWidget(m_gb_flow, 2, 0, 1, 4);

        m_ql_press = new QLabel("P contour");
        qdsb_press_value = new QDoubleSpinBox();

        gl->addWidget(m_ql_press, 3, 0, 1, 2);
        gl->addWidget(qdsb_press_value, 3, 2, 1, 2);
    }

private:
    QGroupBox* m_gb_satur;
    QGroupBox* m_gb_flow;
    QLabel* m_ql_press;
    // QGridLayout* m_layout;

    void setupGbSatur(QWidget* parent)
    {
        m_gb_satur = new QGroupBox("Satur", parent);
        auto layout = new QGridLayout();
        m_gb_satur->setLayout(layout);
    }

    void setupGbFlow(QWidget* parent)
    {
        m_gb_flow = new QGroupBox("Satur", parent);
        auto layout = new QGridLayout();
        m_gb_flow->setLayout(layout);
    }
};

}

#endif
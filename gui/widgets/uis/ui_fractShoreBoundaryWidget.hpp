#ifndef BLE_GUI_WIDGETS_UIS_UIFRACTSHOREBOUNDARYWIDGET_H_
#define BLE_GUI_WIDGETS_UIS_UIFRACTSHOREBOUNDARYWIDGET_H_

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace ble::gui::widgets::UI {

class FractShore {
public:
    QCheckBox* impermeable;
    QDoubleSpinBox* contour_press;
    QLabel* contour_press_label;

    QGroupBox* gb_satur;
    QGroupBox* gb_flow;

    // satur
    QComboBox* satur_distr_type;
    QDoubleSpinBox* satur;
    QLineEdit* satur_file;
    QPushButton* satur_file_button;
    QLabel* satur_label;
    QLabel* satur_file_label;

    // flow
    QGroupBox* gb_q;
    QCheckBox* use_q;
    QComboBox* q_distr_type;
    QDoubleSpinBox* q;
    QLineEdit* q_file;
    QPushButton* q_file_button;
    QLabel* q_label;
    QLabel* q_file_label;

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

        impermeable = new QCheckBox("Impermeable", gb);
        impermeable->setChecked(false);
        gl->addWidget(impermeable, 0, 0, 1, 4);

        gl->addWidget(gb_satur, 1, 0, 1, 4);
        gl->addWidget(gb_flow, 2, 0, 1, 4);
    }

private:
    // satur
    QLabel* m_satur_distr_label;

    // flow
    QLabel* m_q_distr_label;

    void setupGbSatur(QWidget* parent)
    {
        gb_satur = new QGroupBox("Satur", parent);
        auto layout = new QGridLayout();
        gb_satur->setLayout(layout);

        m_satur_distr_label = new QLabel("Type");
        satur_distr_type = new QComboBox();
        layout->addWidget(m_satur_distr_label, 0, 0, 1, 2);
        layout->addWidget(satur_distr_type, 0, 2, 1, 4);

        satur_label = new QLabel("S");
        satur = new QDoubleSpinBox();
        satur->setMinimum(0.0);
        satur->setMaximum(1.0);
        satur->setSingleStep(0.1);
        satur->setValue(1.0);
        layout->addWidget(satur_label, 1, 0, 1, 2);
        layout->addWidget(satur, 1, 2, 1, 4);

        satur_file_label = new QLabel("File");
        satur_file_label->setEnabled(false);
        satur_file = new QLineEdit();
        satur_file->setEnabled(false);
        satur_file_button = new QPushButton("...");
        satur_file_button->setEnabled(false);
        satur_file_button->setStyleSheet("padding: 0px 5px 0px 5px;");
        layout->addWidget(satur_file_label, 2, 0, 1, 2);
        layout->addWidget(satur_file, 2, 2, 1, 3);
        layout->addWidget(satur_file_button, 2, 5, 1, 1);
    }

    void setupGbFlow(QWidget* parent)
    {
        gb_flow = new QGroupBox("Flow", parent);
        auto layout = new QGridLayout();
        gb_flow->setLayout(layout);

        use_q = new QCheckBox("Use q");
        use_q->setChecked(true);
        layout->addWidget(use_q, 0, 0, 1, 4);

        gb_q = new QGroupBox("q");
        auto gbq_layout = new QGridLayout();
        gb_q->setLayout(gbq_layout);

        m_q_distr_label = new QLabel("Type");
        q_distr_type = new QComboBox();
        gbq_layout->addWidget(m_q_distr_label, 0, 0, 1, 2);
        gbq_layout->addWidget(q_distr_type, 0, 2, 1, 4);

        q_label = new QLabel("q, m3/s");
        q = new QDoubleSpinBox();
        q->setMinimum(0.0);
        q->setMaximum(1e5);
        q->setSingleStep(1);
        q->setValue(1.0);
        gbq_layout->addWidget(q_label, 1, 0, 1, 2);
        gbq_layout->addWidget(q, 1, 2, 1, 4);

        q_file_label = new QLabel("File");
        q_file_label->setEnabled(false);
        q_file = new QLineEdit();
        q_file->setEnabled(false);
        q_file_button = new QPushButton("...");
        q_file_button->setEnabled(false);
        q_file_button->setStyleSheet("padding: 0px 5px 0px 5px;");
        gbq_layout->addWidget(q_file_label, 2, 0, 1, 2);
        gbq_layout->addWidget(q_file, 2, 2, 1, 3);
        gbq_layout->addWidget(q_file_button, 2, 5, 1, 1);
        layout->addWidget(gb_q, 1, 0, 1, 6);

        contour_press_label = new QLabel("Pc,at");
        contour_press_label->setEnabled(false);
        contour_press_label->setToolTip("Pressure on contour (at distance L from fracture shore), at");
        contour_press = new QDoubleSpinBox();
        contour_press->setMinimum(-1e8);
        contour_press->setMaximum(1e8);
        contour_press->setValue(150);
        contour_press->setEnabled(false);

        layout->addWidget(contour_press_label, 2, 0, 1, 2);
        layout->addWidget(contour_press, 2, 2, 1, 4);
    }
};

}

#endif
#ifndef BLE_GUI_WIDGETS_UI_SATSOLVERSETTS_H_
#define BLE_GUI_WIDGETS_UI_SATSOLVERSETTS_H_

#include <iostream>
#include <memory>

#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QWidget>

namespace ble::gui::widgets::UI {
class SatSolverSetts {
public:
    QDoubleSpinBox* curant_volume;
    QDoubleSpinBox* curant_face;
    QSpinBox* recalc_press_n;
    QComboBox* solver_type;
    QCheckBox* need_satur_solve;
    QSpinBox* fix_fields_step;
    QSpinBox* max_iter;
    QRadioButton* need_stop_fw_converge;
    QDoubleSpinBox* fw_converge_delta;
    QSpinBox* fw_converge_iter;
    QRadioButton* need_stop_fw_shore_well_converge;
    QDoubleSpinBox* fw_shore_well_converge_value;
    QComboBox* time_step_type;
    QDoubleSpinBox* fw_limit;
    QRadioButton* use_fw_limit;
    QDoubleSpinBox* impl_tau;
    QSpinBox* impl_simple_iter_count;

    QGroupBox* common_gb;
    QGroupBox* stop_crit_gb;
    QGroupBox* explicit_gb;
    QGroupBox* implicit_gb;

    void setupUi(QWidget* widget)
    {
        m_group_box = new QGroupBox();
        m_layout = new QGridLayout(m_group_box);
        m_group_box->setLayout(m_layout);
        m_layout->setMargin(5);

        m_main_layout = new QVBoxLayout(widget);

        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setWidget(m_group_box);
        scrollArea->setWidgetResizable(true);
        m_main_layout->addWidget(scrollArea);

        setupUiCommon();
        setupUiStopCriteria();
        setupUiExplicit();
        setupUiImplicit();

        retranslateUi(widget);
    }

    void retranslateUi(QWidget* widget)
    {
        retranslateUiCommon();
        retranslateUiStopCriteria();
        retranslateUiExplicit();
        retranslateUiImplicit();
    }

private:
    QGroupBox* m_group_box;
    QVBoxLayout* m_main_layout;
    QGridLayout* m_layout;
    QLabel* m_curant_volume_label;
    QLabel* m_curant_face_label;
    QLabel* m_recalc_press_label;
    QLabel* m_solver_type_label;
    QLabel* m_fix_fields_step;
    QLabel* m_max_iter_label;
    QLabel* m_fw_delta_label;
    QLabel* m_fw_converge_iter_label;
    QLabel* m_impl_tau_label;
    QLabel* m_impl_simple_iter_count_label;
    QLabel* m_fw_shore_well_converge_label;
    QLabel* m_timeStepTypeLabel;
    QLabel* m_fw_lim_label;

    void setupUiCommon()
    {
        common_gb = new QGroupBox("Common");
        auto common_layout = new QGridLayout(common_gb);
        common_gb->setLayout(common_layout);
        common_layout->setMargin(5);

        need_satur_solve = new QCheckBox("Solve saturation");
        need_satur_solve->setChecked(true);
        common_layout->addWidget(need_satur_solve, 0, 0);

        m_solver_type_label = new QLabel();
        solver_type = new QComboBox();
        solver_type->setEnabled(true);
        common_layout->addWidget(m_solver_type_label, 1, 0);
        common_layout->addWidget(solver_type, 1, 1);

        m_recalc_press_label = new QLabel();
        recalc_press_n = new QSpinBox();
        recalc_press_n->setMinimum(1);
        recalc_press_n->setMaximum(1e5);
        recalc_press_n->setValue(10);
        common_layout->addWidget(m_recalc_press_label, 2, 0);
        common_layout->addWidget(recalc_press_n, 2, 1);

        m_fix_fields_step = new QLabel();
        fix_fields_step = new QSpinBox();
        fix_fields_step->setMinimum(1);
        fix_fields_step->setMaximum(100000);
        fix_fields_step->setValue(100);
        common_layout->addWidget(m_fix_fields_step, 3, 0);
        common_layout->addWidget(fix_fields_step, 3, 1);

        m_layout->addWidget(common_gb);
    }

    void retranslateUiCommon()
    {
        need_satur_solve->setText("Solve saturation");
        need_satur_solve->setToolTip("Solve saturation");

        m_solver_type_label->setText("Solver type");
        m_solver_type_label->setToolTip("Solver type");

        m_recalc_press_label->setText("Calc press step");
        m_recalc_press_label->setToolTip("Calculate pressure every N saturation calc step");

        m_fix_fields_step->setText("Fix data");
        m_fix_fields_step->setToolTip("Fix data for given step to visualize");
    }

    void setupUiStopCriteria()
    {
        auto setupCriteriaChooseGroupBox = [&]() {
            auto gbCrit = new QGroupBox();
            auto glCrit = new QVBoxLayout();
            gbCrit->setLayout(glCrit);

            need_stop_fw_converge = new QRadioButton("Stop watercut change");
            need_stop_fw_converge->setChecked(false);
            glCrit->addWidget(need_stop_fw_converge, 0);

            need_stop_fw_shore_well_converge = new QRadioButton("Watercut shore|well on converge");
            need_stop_fw_shore_well_converge->setChecked(false);
            glCrit->addWidget(need_stop_fw_shore_well_converge, 1);

            use_fw_limit = new QRadioButton("Use watercut limit");
            use_fw_limit->setChecked(true);
            glCrit->addWidget(use_fw_limit, 2);

            return gbCrit;
        };

        stop_crit_gb = new QGroupBox("Stop criteria");
        auto gl = new QGridLayout(stop_crit_gb);
        stop_crit_gb->setLayout(gl);
        gl->setMargin(5);

        m_max_iter_label = new QLabel("Max iteration");
        max_iter = new QSpinBox();
        max_iter->setMinimum(1);
        max_iter->setMaximum(100000000);
        max_iter->setValue(100000000);
        gl->addWidget(m_max_iter_label, 0, 0);
        gl->addWidget(max_iter, 0, 1);

        auto gb_crit = setupCriteriaChooseGroupBox();
        gl->addWidget(gb_crit, 1, 0, 1, 2);

        m_fw_delta_label = new QLabel();
        fw_converge_delta = new QDoubleSpinBox();
        fw_converge_delta->setDecimals(8);
        fw_converge_delta->setMinimum(1e-8);
        fw_converge_delta->setMaximum(100);
        fw_converge_delta->setSingleStep(1e-8);
        fw_converge_delta->setValue(0.1);
        fw_converge_delta->setEnabled(false);
        gl->addWidget(m_fw_delta_label, 2, 0);
        gl->addWidget(fw_converge_delta, 2, 1);

        m_fw_converge_iter_label = new QLabel("Max iteration");
        fw_converge_iter = new QSpinBox();
        fw_converge_iter->setMinimum(1);
        fw_converge_iter->setMaximum(1e6);
        fw_converge_iter->setValue(100);
        fw_converge_iter->setEnabled(false);
        gl->addWidget(m_fw_converge_iter_label, 3, 0);
        gl->addWidget(fw_converge_iter, 3, 1);

        m_fw_shore_well_converge_label = new QLabel();
        fw_shore_well_converge_value = new QDoubleSpinBox();
        fw_shore_well_converge_value->setDecimals(8);
        fw_shore_well_converge_value->setMinimum(1e-8);
        fw_shore_well_converge_value->setMaximum(100);
        fw_shore_well_converge_value->setSingleStep(1e-8);
        fw_shore_well_converge_value->setValue(1e-1);
        fw_shore_well_converge_value->setEnabled(false);
        gl->addWidget(m_fw_shore_well_converge_label, 5, 0);
        gl->addWidget(fw_shore_well_converge_value, 5, 1);

        m_fw_lim_label = new QLabel("Watercut limit, %");
        fw_limit = new QDoubleSpinBox();
        fw_limit->setMinimum(0.01);
        fw_limit->setMaximum(99);
        fw_limit->setSingleStep(1);
        fw_limit->setValue(98);
        fw_limit->setEnabled(false);
        fw_limit->setToolTip("Set modeling as a critical watercut value on well");
        gl->addWidget(m_fw_lim_label, 6, 0);
        gl->addWidget(fw_limit, 6, 1);

        m_layout->addWidget(stop_crit_gb);
    }

    void retranslateUiStopCriteria()
    {
        m_max_iter_label->setText("Max iteration");
        m_max_iter_label->setToolTip("Max iteration count to stop calc");

        m_fw_delta_label->setText("Watercut delta");
        m_fw_delta_label->setToolTip("Watercut change delta");

        m_fw_converge_iter_label->setText("Watercut delta iter");
        m_fw_converge_iter_label->setToolTip("Watercut change for small delta iter count");

        need_stop_fw_converge->setText("Stop watercut change");
        need_stop_fw_converge->setToolTip("Stop when watercut change less than delta for long iter");

        need_stop_fw_shore_well_converge->setText("Watercut shore|well on converge");
        need_stop_fw_shore_well_converge->setToolTip("Stop when watercut shore|well converged");

        m_fw_shore_well_converge_label->setText("Fw shore|well delta, %");
        m_fw_shore_well_converge_label->setToolTip("Watercut shore|well residual max value to stop calculation");

        m_fw_lim_label->setText("Watercut limit, %");
        m_fw_lim_label->setToolTip("Set modeling as a critical watercut value on well");

        fw_limit->setToolTip("Set modeling as a critical watercut value on well");

        use_fw_limit->setText("Use watercut limit");
        use_fw_limit->setToolTip("Use watercut limit if checked otherwise time limit will be used");
    }

    void setupUiExplicit()
    {
        explicit_gb = new QGroupBox("Explicit");
        auto gl = new QGridLayout(explicit_gb);
        explicit_gb->setLayout(gl);
        gl->setMargin(5);

        m_curant_volume_label = new QLabel();
        curant_volume = new QDoubleSpinBox();
        curant_volume->setDecimals(7);
        curant_volume->setMinimum(1e-6);
        curant_volume->setMaximum(1e6);
        curant_volume->setSingleStep(0.001);
        curant_volume->setValue(0.9);
        gl->addWidget(m_curant_volume_label, 0, 0);
        gl->addWidget(curant_volume, 0, 1);

        m_curant_face_label = new QLabel();
        curant_face = new QDoubleSpinBox();
        curant_face->setDecimals(7);
        curant_face->setMinimum(1e-6);
        curant_face->setMaximum(1e6);
        curant_face->setSingleStep(0.001);
        curant_face->setValue(0.9);
        gl->addWidget(m_curant_face_label, 1, 0);
        gl->addWidget(curant_face, 1, 1);

        m_timeStepTypeLabel = new QLabel();
        time_step_type = new QComboBox();
        gl->addWidget(m_timeStepTypeLabel, 12, 0);
        gl->addWidget(time_step_type, 12, 1);

        m_layout->addWidget(explicit_gb);
    }

    void retranslateUiExplicit()
    {
        m_timeStepTypeLabel->setText("Time step type");
        m_timeStepTypeLabel->setToolTip("Time step define type");

        m_curant_volume_label->setText("Curant (volume)");
        m_curant_volume_label->setToolTip("Curant number for grid cell");

        m_curant_face_label->setText("Curant (face)");
        m_curant_face_label->setToolTip("Curant number for grid faces");
    }

    void setupUiImplicit()
    {
        implicit_gb = new QGroupBox("Implicit");
        auto gl = new QGridLayout(implicit_gb);
        implicit_gb->setLayout(gl);
        gl->setMargin(5);

        m_impl_tau_label = new QLabel();
        impl_tau = new QDoubleSpinBox();
        impl_tau->setDecimals(8);
        impl_tau->setMinimum(1e-8);
        impl_tau->setMaximum(100);
        impl_tau->setSingleStep(1e-8);
        impl_tau->setValue(1e-3);
        gl->addWidget(m_impl_tau_label, 0, 0);
        gl->addWidget(impl_tau, 0, 1);

        m_impl_simple_iter_count_label = new QLabel();
        impl_simple_iter_count = new QSpinBox();
        impl_simple_iter_count->setMinimum(1);
        impl_simple_iter_count->setMaximum(100);
        impl_simple_iter_count->setValue(3);
        gl->addWidget(m_impl_simple_iter_count_label, 1, 0);
        gl->addWidget(impl_simple_iter_count, 1, 1);

        m_layout->addWidget(implicit_gb);
    }

    void retranslateUiImplicit()
    {
        m_impl_tau_label->setText("Tau");
        m_impl_tau_label->setToolTip("Tau for fim");

        m_impl_simple_iter_count_label->setText("Simple iter");
        m_impl_simple_iter_count_label->setToolTip("Iter via simple method before Newton method");
    }
};

}

#endif
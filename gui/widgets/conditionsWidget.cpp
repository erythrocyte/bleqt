/*
 * Filename: boundaryConditionsWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Saturday, September 25th 2021, 9:05:47 am
 * Author: erythrocyte
 *
 * Copyright (c) 2021 Your Company
 */

#include "conditionsWidget.hpp"

#include <QFileDialog>

#include "common/models/dataDistributionType.hpp"
#include "common/services/dataDistributionService.hpp"

#include "utils/qwidgetUtils.hpp"

namespace scmm = ble::src::common::models;
namespace scms = ble::src::common::services;

namespace ble::gui::widgets {

ConditionsWidget::ConditionsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::Conditions)
{
    ui->setupUI(this);
    set_items();

    subscribe();

    emit rhs_updated();
}

void ConditionsWidget::set_items()
{
    for (scmm::DataDistributionType::TypeEnum v : scmm::DataDistributionTypeEnumIterator()) {
        auto item = QString::fromStdString(scmm::DataDistributionType::get_description(v));
        ui->init_satur_type->addItem(item);
        ui->fract_shores_left_right->ui->q_distr_type->addItem(item);
        ui->fract_shores_left_right->ui->satur_distr_type->addItem(item);
    }
}

void ConditionsWidget::subscribe()
{
    // success = QObject::connect(ui->TopBotBoundConstLenght, SIGNAL(valueChanged(int)), this, SLOT(onTopBotBoundLenghtChanged(int)));
    // Q_ASSERT(success);
    // success = QObject::connect(ui->BoundSConstValue, SIGNAL(valueChanged(double)), this, SLOT(onBoundSConstValueChanged(double)));
    // Q_ASSERT(success);
    // success = QObject::connect(ui->BoundSFileChooseButton, SIGNAL(clicked()), this, SLOT(fileBoundSChooseClicked()));
    // success = QObject::connect(ui->BoundSType, SIGNAL(currentIndexChanged(const QString&)),
    //     this, SLOT(topBotBoundSTypeChanged(const QString&)));

    // init
    auto success = QObject::connect(ui->init_satur_type, QOverload<const QString&>::of(&QComboBox::currentIndexChanged),
        this, &ConditionsWidget::initSaturTypeChanged);
    success = QObject::connect(ui->init_satur_file_button, &QPushButton::clicked,
        this, &ConditionsWidget::initSaturFileChosen);
    success = QObject::connect(ui->init_satur, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &ConditionsWidget::initSatConstChanged);

    // bound satur
    success = QObject::connect(ui->fract_shores_left_right->ui->satur_distr_type, QOverload<const QString&>::of(&QComboBox::currentIndexChanged),
        this, &ConditionsWidget::boundSaturTypeChanged);
    success = QObject::connect(ui->fract_shores_left_right->ui->satur_file_button, &QPushButton::clicked,
        this, &ConditionsWidget::boundSaturFileChosen);
    success = QObject::connect(ui->fract_shores_left_right->ui->satur, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &ConditionsWidget::boundSaturConstChanged);

    // bound q
    success = QObject::connect(ui->fract_shores_left_right->ui->q_distr_type, QOverload<const QString&>::of(&QComboBox::currentIndexChanged),
        this, &ConditionsWidget::qTypeChanged);
    success = QObject::connect(ui->fract_shores_left_right->ui->q_file_button, &QPushButton::clicked,
        this, &ConditionsWidget::qFileChosen);
    success = QObject::connect(ui->fract_shores_left_right->ui->q, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
        this, &ConditionsWidget::qConstChanged);
    success = QObject::connect(ui->fract_shores_left_right->ui->use_q, &QCheckBox::toggled,
        this, &ConditionsWidget::useQChecked);
    success = QObject::connect(ui->fract_shores_left_right->ui->impermeable, &QCheckBox::toggled,
        this, &ConditionsWidget::impermChecked);

    success = QObject::connect(ui->fract_end_imperm, &QCheckBox::toggled, this,
        &ConditionsWidget::fractEndImperChecked);
    Q_ASSERT(success);
}

void ConditionsWidget::initSatConstChanged(double value)
{
    emit init_updated();
}

void ConditionsWidget::initSaturFileChosen(bool checked)
{
    QString file_name = get_choosed_file();
    if (!file_name.trimmed().isEmpty()) {
        ui->init_satur_file->setText(file_name);
        emit init_updated();
    }
}

void ConditionsWidget::qConstChanged(double value)
{
    emit rhs_updated();
}

void ConditionsWidget::qFileChosen(bool checked)
{
    QString file_name = get_choosed_file();
    if (!file_name.trimmed().isEmpty()) {
        ui->fract_shores_left_right->ui->q_file->setText(file_name);
        emit init_updated();
    }
}

void ConditionsWidget::qTypeChanged(const QString& value)
{
    auto m = scmm::DataDistributionType::get_enum(value.toStdString());

    // auto children = gui::utils::QWidgetUtils::getChildWidgets(ui->gb_init);
    // for (auto const child : children) {
    //     child->setEnabled(false);
    // }

    ui->fract_shores_left_right->ui->q_label->setEnabled(false);
    ui->fract_shores_left_right->ui->q->setEnabled(false);
    ui->fract_shores_left_right->ui->q_file->setEnabled(false);
    ui->fract_shores_left_right->ui->q_file_button->setEnabled(false);
    ui->fract_shores_left_right->ui->q_file_label->setEnabled(false);

    if (m == scmm::DataDistributionType::kConst) { // in this way with if, coz it is possible to be more then 2 branches
        ui->fract_shores_left_right->ui->q_label->setEnabled(true);
        ui->fract_shores_left_right->ui->q->setEnabled(true);
    } else if (m == scmm::DataDistributionType::kFile) {
        ui->fract_shores_left_right->ui->q_file->setEnabled(true);
        ui->fract_shores_left_right->ui->q_file_button->setEnabled(true);
        ui->fract_shores_left_right->ui->q_file_label->setEnabled(true);
    }

    emit rhs_updated();
}

void ConditionsWidget::boundSaturConstChanged(double value)
{
    emit rhs_updated();
}

void ConditionsWidget::boundSaturFileChosen(bool checked)
{
    QString file_name = get_choosed_file();
    if (!file_name.trimmed().isEmpty()) {
        ui->fract_shores_left_right->ui->satur_file->setText(file_name);
        emit init_updated();
    }
}

void ConditionsWidget::boundSaturTypeChanged(const QString& value)
{
    auto m = scmm::DataDistributionType::get_enum(value.toStdString());

    // auto children = gui::utils::QWidgetUtils::getChildWidgets(ui->gb_init);
    // for (auto const child : children) {
    //     child->setEnabled(false);
    // }

    ui->fract_shores_left_right->ui->satur_label->setEnabled(false);
    ui->fract_shores_left_right->ui->satur->setEnabled(false);
    ui->fract_shores_left_right->ui->satur_file->setEnabled(false);
    ui->fract_shores_left_right->ui->satur_file_button->setEnabled(false);
    ui->fract_shores_left_right->ui->satur_file_label->setEnabled(false);

    if (m == scmm::DataDistributionType::kConst) { // in this way with if, coz it is possible to be more then 2 branches
        ui->fract_shores_left_right->ui->satur->setEnabled(true);
        ui->fract_shores_left_right->ui->satur_label->setEnabled(true);
    } else if (m == scmm::DataDistributionType::kFile) {
        ui->fract_shores_left_right->ui->satur_file->setEnabled(true);
        ui->fract_shores_left_right->ui->satur_file_button->setEnabled(true);
        ui->fract_shores_left_right->ui->satur_file_label->setEnabled(true);
    }

    emit rhs_updated();
}

void ConditionsWidget::initSaturTypeChanged(const QString& value)
{
    auto m = scmm::DataDistributionType::get_enum(value.toStdString());

    // auto children = gui::utils::QWidgetUtils::getChildWidgets(ui->gb_init);
    // for (auto const child : children) {
    //     child->setEnabled(false);
    // }

    ui->init_satur->setEnabled(false);
    ui->init_satur_label->setEnabled(false);
    ui->init_satur_file->setEnabled(false);
    ui->init_satur_file_button->setEnabled(false);
    ui->init_satur_file_label->setEnabled(false);

    if (m == scmm::DataDistributionType::kConst) { // in this way with if, coz it is possible to be more then 2 branches
        ui->init_satur->setEnabled(true);
        ui->init_satur_label->setEnabled(true);
    } else if (m == scmm::DataDistributionType::kFile) {
        ui->init_satur_file->setEnabled(true);
        ui->init_satur_file_button->setEnabled(true);
        ui->init_satur_file_label->setEnabled(true);
    }

    emit init_updated();
}

void ConditionsWidget::fractEndImperChecked(bool state)
{
    ui->p_fract_end_label->setEnabled(!state);
    ui->s_fract_end_label->setEnabled(!state);
    ui->press_fract_end->setEnabled(!state);
    ui->sat_fract_end->setEnabled(!state);
}

QString ConditionsWidget::get_choosed_file()
{
    QString filter = tr("BLERHS (*.blerhs)");
    QString file_name = QFileDialog::getOpenFileName(
        this,
        "Open RHS file",
        "",
        tr("BLERHS (*.blerhs)"),
        &filter);

    return file_name;
}

std::shared_ptr<src::common::models::BoundCondData> ConditionsWidget::get_bound_data(double x0, double x1)
{
    std::shared_ptr<src::common::models::BoundCondData> result = std::make_shared<src::common::models::BoundCondData>();

    // fract end;
    result->fract_end_imperm = ui->fract_end_imperm->isChecked();
    result->fract_end_satur = ui->sat_fract_end->value();
    result->fract_end_press = ui->press_fract_end->value();

    // fract shore
    std::string str = ui->fract_shores_left_right->ui->satur_distr_type->currentText().toStdString();
    result->fract_shore_s_type = src::common::models::DataDistributionType::get_enum(str);
    switch (result->fract_shore_s_type) {
    case src::common::models::DataDistributionType::kConst: {
        double val = ui->fract_shores_left_right->ui->satur->value();
        int len_right_perc = 100;
        result->fract_shore_s = scms::DataDistributionService::get_data_from_const(val, len_right_perc, x0, x1);
        break;
    }
    case src::common::models::DataDistributionType::kFile: {
        std::string file_name = ui->fract_shores_left_right->ui->satur_file->text().toStdString();
        result->fract_shore_s = scms::DataDistributionService::get_data_from_file(file_name);
        break;
    }
    default:
        break;
    }

    str = ui->fract_shores_left_right->ui->q_distr_type->currentText().toStdString();
    result->fract_shore_q_type = src::common::models::DataDistributionType::get_enum(str);
    switch (result->fract_shore_q_type) {
    case src::common::models::DataDistributionType::kConst: {
        double val = ui->fract_shores_left_right->ui->q->value();
        int len_right_perc = 100;
        result->fract_shore_q = scms::DataDistributionService::get_data_from_const(val, len_right_perc, x0, x1);
        break;
    }
    case src::common::models::DataDistributionType::kFile: {
        std::string file_name = ui->fract_shores_left_right->ui->q_file->text().toStdString();
        result->fract_shore_q = scms::DataDistributionService::get_data_from_file(file_name);
        break;
    }
    default:
        break;
    }
    result->fract_shore_imperm = ui->fract_shores_left_right->ui->impermeable->isChecked();
    result->pc = ui->fract_shores_left_right->ui->contour_press->value();
    result->use_q = ui->fract_shores_left_right->ui->use_q->isChecked();

    // well
    result->pw = ui->p_well->value();
    result->sw = ui->s_well->value();

    // initial
    str = ui->init_satur_type->currentText().toStdString();
    result->initial_satur_type = src::common::models::DataDistributionType::get_enum(str);
    switch (result->initial_satur_type) {
    case src::common::models::DataDistributionType::kConst: {
        double val = ui->init_satur->value();
        int len_right_perc = 100;
        result->initial_s = scms::DataDistributionService::get_data_from_const(val, len_right_perc, x0, x1);
        break;
    }
    case src::common::models::DataDistributionType::kFile: {
        std::string file_name = ui->init_satur_file->text().toStdString();
        result->initial_s = scms::DataDistributionService::get_data_from_file(file_name);
        break;
    }
    default:
        break;
    }

    return result;
}

void ConditionsWidget::useQChecked(bool checked)
{
    ui->fract_shores_left_right->ui->gb_q->setEnabled(checked);
    ui->fract_shores_left_right->ui->contour_press->setEnabled(!checked);
    ui->fract_shores_left_right->ui->contour_press_label->setEnabled(!checked);
}

void ConditionsWidget::impermChecked(bool checked)
{
    ui->fract_shores_left_right->ui->gb_satur->setEnabled(!checked);
    ui->fract_shores_left_right->ui->gb_flow->setEnabled(!checked);
}

}

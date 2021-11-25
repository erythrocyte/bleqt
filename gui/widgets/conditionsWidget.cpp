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

#include "common/models/boundCondType.hpp"
#include "common/models/dataDistributionType.hpp"
#include "common/services/dataDistributionService.hpp"

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

    ui->ContourBoundType->setCurrentIndex(1);
    ui->BoundSType->setCurrentIndex(1);
    ui->BoundSFile->setText("../../samples/rhs/s_sample.blerhs");
    emit rhs_updated();
}

void ConditionsWidget::set_items()
{
    for (scmm::BoundCondType::TypeEnum v : scmm::BoundCondTypeEnumIterator()) {
        ui->ContourBoundType->addItem(QString::fromStdString(scmm::BoundCondType::get_description(v)));
    }

    for (scmm::DataDistributionType::TypeEnum v : scmm::DataDistributionTypeEnumIterator()) {
        ui->InitialSaturType->addItem(QString::fromStdString(scmm::DataDistributionType::get_description(v)));
    }

    for (scmm::DataDistributionType::TypeEnum v : scmm::DataDistributionTypeEnumIterator()) {
        ui->BoundSType->addItem(QString::fromStdString(scmm::DataDistributionType::get_description(v)));
    }
}

void ConditionsWidget::subscribe()
{
    auto success = QObject::connect(ui->ContourBoundType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(contourTypeChanged(const QString&)));
    Q_ASSERT(success);
    success = QObject::connect(ui->TopBotBoundConstLenght, SIGNAL(valueChanged(int)), this, SLOT(onTopBotBoundLenghtChanged(int)));
    Q_ASSERT(success);
    success = QObject::connect(ui->BoundSConstValue, SIGNAL(valueChanged(double)), this, SLOT(onBoundSConstValueChanged(double)));
    Q_ASSERT(success);
    success = QObject::connect(ui->BoundSFileChooseButton, SIGNAL(clicked()), this, SLOT(fileBoundSChooseClicked()));
    success = QObject::connect(ui->BoundSType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(topBotBoundSTypeChanged(const QString&)));
}

void ConditionsWidget::contourTypeChanged(const QString& value)
{
    auto m = scmm::BoundCondType::get_enum(value.toStdString());
    if (m == scmm::BoundCondType::kConst) {
        ui->TopBotBoundConstLenght->setEnabled(false);
        ui->BoundSType->setEnabled(false);
        ui->BoundSConstValue->setEnabled(false);
        ui->BoundSFile->setEnabled(false);
        ui->BoundSFileChooseButton->setEnabled(false);
        ui->BoundSatur->setEnabled(true);
    } else if (m == scmm::BoundCondType::kImpermeable) {
        ui->BoundSType->setEnabled(true);
        topBotBoundSTypeChanged(ui->BoundSType->currentText());
        ui->BoundSatur->setEnabled(false);
    }
}

void ConditionsWidget::topBotBoundSTypeChanged(const QString& value)
{
    auto m = scmm::DataDistributionType::get_enum(value.toStdString());
    switch (m) {
    case scmm::DataDistributionType::kConst:
        ui->BoundSConstValue->setEnabled(true);
        ui->BoundSFile->setEnabled(false);
        ui->BoundSFileChooseButton->setEnabled(false);
        break;
    case scmm::DataDistributionType::kFile:
        ui->BoundSConstValue->setEnabled(false);
        ui->BoundSFile->setEnabled(true);
        ui->BoundSFileChooseButton->setEnabled(true);
        break;
    }
    emit rhs_updated();
}

void ConditionsWidget::fileBoundSChooseClicked()
{
    QString file_name = get_choosed_file();
    if (!file_name.trimmed().isEmpty()) {
        ui->BoundSFile->setText(file_name);
        emit rhs_updated();
    }
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

    std::string str = ui->ContourBoundType->currentText().toStdString();
    result->contour_press_bound_type = src::common::models::BoundCondType::get_enum(str);

    str = ui->BoundSType->currentText().toStdString();
    result->top_bot_bound_s_type = src::common::models::DataDistributionType::get_enum(str);
    switch (result->top_bot_bound_s_type) {
    case src::common::models::DataDistributionType::kConst: {
        double val = ui->BoundSConstValue->value();
        int len_right_perc = ui->TopBotBoundConstLenght->value();
        result->top_bot_bound_s = scms::DataDistributionService::get_data_from_const(val, len_right_perc, x0, x1);
        break;
    }
    case src::common::models::DataDistributionType::kFile: {
        std::string file_name = ui->BoundSFile->text().toStdString();
        result->top_bot_bound_s = scms::DataDistributionService::get_data_from_file(file_name);
        break;
    }
    default:
        break;
    }

    result->bound_satur = ui->BoundSatur->value();
    result->pc = ui->PressureContour->value();
    result->pw = ui->PressureWell->value();

    return result;
}

void ConditionsWidget::onTopBotBoundLenghtChanged(int value)
{
    emit rhs_updated();
}

void ConditionsWidget::onBoundUConstValueChanged(double value)
{
    emit rhs_updated();
}

void ConditionsWidget::onBoundSConstValueChanged(double value)
{
    emit rhs_updated();
}

}

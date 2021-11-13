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
}

void ConditionsWidget::set_items()
{
    for (scmm::BoundCondType::TypeEnum v : scmm::BoundCondTypeEnumIterator()) {
        ui->ContourBoundType->addItem(QString::fromStdString(scmm::BoundCondType::get_description(v)));
    }

    for (scmm::DataDistributionType::TypeEnum v : scmm::DataDistributionTypeEnumIterator()) {
        ui->TopBotCondType->addItem(QString::fromStdString(scmm::DataDistributionType::get_description(v)));
    }

    for (scmm::DataDistributionType::TypeEnum v : scmm::DataDistributionTypeEnumIterator()) {
        ui->InitialSaturType->addItem(QString::fromStdString(scmm::DataDistributionType::get_description(v)));
    }
}

void ConditionsWidget::subscribe()
{
    auto success = QObject::connect(ui->ContourBoundType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(contourTypeChanged(const QString&)));
    Q_ASSERT(success);
    success = QObject::connect(ui->TopBotCondType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(topBotBoundTypeChanged(const QString&)));
    Q_ASSERT(success);
    success = QObject::connect(ui->BoundUFileChooseButton, SIGNAL(clicked()), this, SLOT(fileChooseClicked()));
    Q_ASSERT(success);
    success = QObject::connect(ui->BoundUConstValue, SIGNAL(valueChanged(double)), this, SLOT(onBoundUConstValueChanged(double)));
    Q_ASSERT(success);
    success = QObject::connect(ui->TopBotBoundConstLenght, SIGNAL(valueChanged(int)), this, SLOT(onTopBotBoundLenghtChanged(int)));
    Q_ASSERT(success);
}

void ConditionsWidget::contourTypeChanged(const QString& value)
{
    auto m = scmm::BoundCondType::get_enum(value.toStdString());
    if (m == scmm::BoundCondType::kConst) {
        ui->TopBotCondType->setEnabled(false);
        ui->BoundUConstValue->setEnabled(false);
        ui->BoundUFile->setEnabled(false);
        ui->BoundUFileChooseButton->setEnabled(false);
        ui->TopBotBoundConstLenght->setEnabled(false);
    } else if (m == scmm::BoundCondType::kImpermeable) {
        ui->TopBotCondType->setEnabled(true);
        topBotBoundTypeChanged(ui->TopBotCondType->currentText());
    }
}

void ConditionsWidget::topBotBoundTypeChanged(const QString& value)
{
    auto m = scmm::DataDistributionType::get_enum(value.toStdString());
    switch (m) {
    case scmm::DataDistributionType::kConst:
        ui->BoundUConstValue->setEnabled(true);
        ui->TopBotBoundConstLenght->setEnabled(true);
        ui->BoundUFile->setEnabled(false);
        ui->BoundUFileChooseButton->setEnabled(false);
        break;
    case scmm::DataDistributionType::kFile:
        ui->BoundUConstValue->setEnabled(false);
        ui->TopBotBoundConstLenght->setEnabled(false);
        ui->BoundUFile->setEnabled(true);
        ui->BoundUFileChooseButton->setEnabled(true);
        break;
    }
    emit rhs_updated();
}

void ConditionsWidget::fileChooseClicked()
{
    QString filter = tr("BLERHS (*.blerhs)");
    QString file_name = QFileDialog::getOpenFileName(
        this,
        "Open RHS file",
        "",
        tr("BLERHS (*.blerhs)"),
        &filter);

    if (!file_name.trimmed().isEmpty()) {
        ui->BoundUFile->setText(file_name);
        emit rhs_updated();
    }
}

std::shared_ptr<src::common::models::BoundCondData> ConditionsWidget::get_bound_data(double x0, double x1)
{
    std::shared_ptr<src::common::models::BoundCondData> result = std::make_shared<src::common::models::BoundCondData>();

    std::string str = ui->ContourBoundType->currentText().toStdString();
    result->contour_press_bound_type = src::common::models::BoundCondType::get_enum(str);

    str = ui->TopBotCondType->currentText().toStdString();
    result->top_bot_bound_u_type = src::common::models::DataDistributionType::get_enum(str);

    switch (result->top_bot_bound_u_type) {
    case src::common::models::DataDistributionType::kConst: {
        double val = ui->BoundUConstValue->value();
        int len_right_perc = ui->TopBotBoundConstLenght->value();
        result->top_bot_bound_u = scms::DataDistributionService::get_data_from_const(val, len_right_perc, x0, x1);
        break;
    }
    case src::common::models::DataDistributionType::kFile: {
        std::string file_name = ui->BoundUFile->text().toStdString();
        result->top_bot_bound_u = scms::DataDistributionService::get_data_from_file(file_name);
        break;
    }
    default:
        break;
    }

    result->bound_satur = ui->BoundSatur->value();

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

}

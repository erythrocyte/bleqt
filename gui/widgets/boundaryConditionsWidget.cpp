/*
 * Filename: boundaryConditionsWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Saturday, September 25th 2021, 9:05:47 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "boundaryConditionsWidget.hpp"

#include <QFileDialog>

#include "common/models/boundCondType.hpp"
#include "common/models/rhsType.hpp"
#include "common/services/dataDistributionService.hpp"

namespace scmm = ble::src::common::models;
namespace scms = ble::src::common::services;

namespace ble::gui::widgets {

BoundaryConditionsWidget::BoundaryConditionsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::BoundaryConditions)
{
    ui->setupUI(this);
    set_items();

    subscribe();

    ui->ContourBoundType->setCurrentIndex(1);
}

void BoundaryConditionsWidget::set_items()
{
    for (scmm::BoundCondType::TypeEnum v : scmm::BoundCondTypeEnumIterator()) {
        ui->ContourBoundType->addItem(QString::fromStdString(scmm::BoundCondType::get_description(v)));
    }

    for (scmm::RHSType::TypeEnum v : scmm::RHSTypeEnumIterator()) {
        ui->RHSType->addItem(QString::fromStdString(scmm::RHSType::get_description(v)));
    }
}

void BoundaryConditionsWidget::subscribe()
{
    auto success = QObject::connect(ui->ContourBoundType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(contourTypeChanged(const QString&)));
    Q_ASSERT(success);
    success = QObject::connect(ui->RHSType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(rhsTypeChanged(const QString&)));
    Q_ASSERT(success);
    success = QObject::connect(ui->RHSFileChooseButton, SIGNAL(clicked()), this, SLOT(fileChooseClicked()));
    Q_ASSERT(success);
    success = QObject::connect(ui->RHSConstValue, SIGNAL(valueChanged(double)), this, SLOT(onRhsConstValueChanged(double)));
    Q_ASSERT(success);
    success = QObject::connect(ui->RHSConstLenght, SIGNAL(valueChanged(int)), this, SLOT(onRhsConstLenghtChanged(int)));
    Q_ASSERT(success);
}

void BoundaryConditionsWidget::contourTypeChanged(const QString& value)
{
    auto m = scmm::BoundCondType::get_enum(value.toStdString());
    if (m == scmm::BoundCondType::kConst) {
        ui->RHSType->setEnabled(false);
        ui->RHSConstValue->setEnabled(false);
        ui->RHSFile->setEnabled(false);
        ui->RHSFileChooseButton->setEnabled(false);
        ui->RHSConstLenght->setEnabled(false);
    } else if (m == scmm::BoundCondType::kImpermeable) {
        ui->RHSType->setEnabled(true);
        rhsTypeChanged(ui->RHSType->currentText());
    }
}

void BoundaryConditionsWidget::rhsTypeChanged(const QString& value)
{
    auto m = scmm::RHSType::get_enum(value.toStdString());
    if (m == scmm::RHSType::kConst) {
        ui->RHSConstValue->setEnabled(true);
        ui->RHSConstLenght->setEnabled(true);
        ui->RHSFile->setEnabled(false);
        ui->RHSFileChooseButton->setEnabled(false);
    } else if (m == scmm::RHSType::kFile) {
        ui->RHSConstValue->setEnabled(false);
        ui->RHSConstLenght->setEnabled(false);
        ui->RHSFile->setEnabled(true);
        ui->RHSFileChooseButton->setEnabled(true);
    }
    emit rhs_updated();
}

void BoundaryConditionsWidget::fileChooseClicked()
{
    QString filter = tr("BLERHS (*.blerhs)");
    QString file_name = QFileDialog::getOpenFileName(
        this,
        "Open RHS file",
        "",
        tr("BLERHS (*.blerhs)"),
        &filter);

    if (!file_name.trimmed().isEmpty()) {
        ui->RHSFile->setText(file_name);
        emit rhs_updated();
    }
}

std::shared_ptr<src::common::models::BoundCondData> BoundaryConditionsWidget::get_bound_data(double x0, double x1)
{
    std::shared_ptr<src::common::models::BoundCondData> result = std::make_shared<src::common::models::BoundCondData>();

    std::string str = ui->ContourBoundType->currentText().toStdString();
    result->contour_press_bound_type = src::common::models::BoundCondType::get_enum(str);

    str = ui->RHSType->currentText().toStdString();
    result->top_bot_bound_u_type = src::common::models::RHSType::get_enum(str);

    switch (result->top_bot_bound_u_type) {
    case src::common::models::RHSType::kConst: {
        double val = ui->RHSConstValue->value();
        int len_right_perc = ui->RHSConstLenght->value();
        result->top_bot_bound_u = scms::DataDistributionService::get_data_from_const(val, len_right_perc, x0, x1);
        break;
    }
    case src::common::models::RHSType::kFile: {
        std::string file_name = ui->RHSFile->text().toStdString();
        result->top_bot_bound_u = scms::DataDistributionService::get_data_from_file(file_name);
        break;
    }
    default:
        break;
    }

    return result;
}

void BoundaryConditionsWidget::onRhsConstLenghtChanged(int value)
{
    emit rhs_updated();
}

void BoundaryConditionsWidget::onRhsConstValueChanged(double value)
{
    emit rhs_updated();
}

}

/*
 * Filename: boundaryConditionsWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Saturday, September 25th 2021, 9:05:47 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "boundaryConditionsWidget.hpp"

#include "common/models/boundCondType.hpp"
#include "common/models/rhsType.hpp"

namespace scmm = ble::src::common::models;

namespace ble::gui::widgets {

BoundaryConditionsWidget::BoundaryConditionsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::BoundaryConditions)
{
    ui->setupUI(this);
    set_items();
    subscribe();
}

void BoundaryConditionsWidget::set_items()
{
    for (scmm::BoundCondType::TypeEnum v : scmm::BoundCondTypeEnumIterator()) {
        ui->ContourBondType->addItem(QString::fromStdString(scmm::BoundCondType::get_description(v)));
    }

    for (scmm::RHSType::TypeEnum v : scmm::RHSTypeEnumIterator()) {
        ui->RHSType->addItem(QString::fromStdString(scmm::RHSType::get_description(v)));
    }
}

void BoundaryConditionsWidget::subscribe()
{
    auto success = QObject::connect(ui->ContourBondType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(contourTypeChanged(const QString&)));
    Q_ASSERT(success);
    success = QObject::connect(ui->RHSType, SIGNAL(currentIndexChanged(const QString&)),
        this, SLOT(rhsTypeChanged(const QString&)));
    Q_ASSERT(success);
}

void BoundaryConditionsWidget::contourTypeChanged(const QString& value)
{
    auto m = scmm::BoundCondType::get_enum(value.toStdString());
    if (m == scmm::BoundCondType::kConst) {
        ui->RHSType->setEnabled(false);
        ui->RHSFile->setEnabled(false);
        ui->RHSFileChooseButton->setEnabled(false);
    }
    else if (m == scmm::BoundCondType::kImpermeable)
    {
        ui->RHSType->setEnabled(true);
        ui->RHSFile->setEnabled(true);
        ui->RHSFileChooseButton->setEnabled(true);
    }
}

void BoundaryConditionsWidget::rhsTypeChanged(const QString& value)
{
}

}

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
#include "common/services/boundSourceService.hpp"

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
}

void BoundaryConditionsWidget::contourTypeChanged(const QString& value)
{
    auto m = scmm::BoundCondType::get_enum(value.toStdString());
    if (m == scmm::BoundCondType::kConst) {
        ui->RHSType->setEnabled(false);
        ui->RHSFile->setEnabled(false);
        ui->RHSFileChooseButton->setEnabled(false);
        get_bound_data(prepare_data(false));
    } else if (m == scmm::BoundCondType::kImpermeable) {
        ui->RHSType->setEnabled(true);
        ui->RHSFile->setEnabled(true);
        ui->RHSFileChooseButton->setEnabled(true);
    }
}

void BoundaryConditionsWidget::rhsTypeChanged(const QString& value)
{
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
        get_bound_data(prepare_data(true));
    }
}

std::shared_ptr<src::common::models::BoundCondData> BoundaryConditionsWidget::prepare_data(bool is_file)
{
    std::shared_ptr<src::common::models::BoundCondData> result = std::make_shared<src::common::models::BoundCondData>();
    std::string file_name = ui->RHSFile->text().toStdString();
    auto tp = src::common::models::BoundCondType::get_enum(ui->RHSType->currentText().toStdString());
    result->bound_type = tp;
    if (is_file) {
        result->bound_sources = scms::BoundSourceService::get_data(file_name);
    }
    return result;
}

}

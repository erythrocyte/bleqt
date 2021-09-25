/*
 * Filename: boundaryConditionsWidget.cpp
 * Path: bleqt/gui/widgets
 * Created Date: Saturday, September 25th 2021, 9:05:47 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "boundaryConditionsWidget.hpp"

namespace ble::gui::widgets {

BoundaryConditionsWidget::BoundaryConditionsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::BoundaryConditions)
{
    ui->setupUI(this);
}

}

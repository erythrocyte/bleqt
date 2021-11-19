/*
 * Filename: tauModel.hpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Friday, November 19th 2021, 6:04:27 pm
 * Author: erythrocyte
 *
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_MODELS_TAUMODEL_H_
#define BLE_GUI_WIDGETS_MODELS_TAUMODEL_H_

#include <iostream>
#include <memory>
#include <vector>

#include <QAbstractTableModel>

#include "common/models/tauData.hpp"

namespace ble::gui::widgets::models {

class TauModel : public QAbstractTableModel {
    Q_OBJECT

public:
    TauModel(
        const std::vector<std::shared_ptr<src::common::models::TauData>>& data,
        QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<std::shared_ptr<src::common::models::TauData>> m_data;
    double empty_val;
};

}

#endif
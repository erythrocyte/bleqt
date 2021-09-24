/*
 * Filename: wellWorkParamsModel.hpp
 * Path: bleqt/gui/models
 * Created Date: Thursday, September 23rd 2021, 8:44:10 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_MODELS_WELLWORKPARAMSMODEL_H_
#define BLE_GUI_WIDGETS_MODELS_WELLWORKPARAMSMODEL_H_

#include <memory>
#include <vector>

#include <QAbstractTableModel>

#include "common/models/wellWorkParams.hpp"

namespace ble::gui::widgets::models {

class WellWorkParamsModel : public QAbstractTableModel {
    Q_OBJECT

public:
    WellWorkParamsModel(const std::vector<std::shared_ptr<ble::src::common::models::WellWorkParams>> data, QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool is_yaxis_left(int section);

private:
    std::vector<std::shared_ptr<ble::src::common::models::WellWorkParams>> m_data;
    const double EMPTY_VAL = -99999.0;

    bool is_empty(double value) const;
};

}

#endif

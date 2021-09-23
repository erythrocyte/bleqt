/*
 * Filename: wellWorkParamsModel.cpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Thursday, September 23rd 2021, 11:09:23 pm
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "wellWorkParamsModel.hpp"

namespace ble::gui::widgets::models {

WellWorkParamsModel::WellWorkParamsModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

WellWorkParamsModel::WellWorkParamsModel(const std::vector<std::shared_ptr<ble_src::common::models::WellWorkParams>> data,
    QObject* parent)
    : QAbstractTableModel(parent)
{
    m_data = data;
}

QVariant WellWorkParamsModel::data(const QModelIndex& index, int role) const
{
    auto get_value = [&]() {
        int row_index = index.row(), column_index = index.column();

        switch (column_index) {
        case 0:
            return m_data[row_index]->t;
        case 1:
            return m_data[row_index]->ql;
        case 2:
            return m_data[row_index]->qo;
        case 3:
            return m_data[row_index]->qw;
        default:
            return m_data[row_index]->fw;
        }
    };

    if (role == Qt::DisplayRole) {

        auto value = get_value();
        return QString("%.4f").arg(value);
    }

    return QVariant();
}

int WellWorkParamsModel::rowCount(const QModelIndex& parent) const { return row_count; }
int WellWorkParamsModel::columnCount(const QModelIndex& parent) const { return 5; }

QVariant WellWorkParamsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

}

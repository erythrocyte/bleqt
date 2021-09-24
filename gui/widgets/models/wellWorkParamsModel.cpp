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
        return QString("%1")
            .arg(get_value());
    }

    return QVariant();
}

int WellWorkParamsModel::rowCount(const QModelIndex& parent) const { return m_data.size(); }
int WellWorkParamsModel::columnCount(const QModelIndex& parent) const { return 5; }

QVariant WellWorkParamsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("%1").arg("t");
        case 1:
            return QString("%1").arg("qw");
        case 2:
            return QString("%1").arg("ql");
        case 3:
            return QString("%1").arg("qo");
        case 4:
            return QString("%1").arg("fw");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

bool WellWorkParamsModel::is_yaxis_left(int section)
{
    switch (section) {
    case 1:
        return true; // qw;
    case 2:
        return true; // ql;
    case 3:
        return true; // qo;
    case 4:
        return false; // fw;
    default:
        return true;
    }
}

}

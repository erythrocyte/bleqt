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

WellWorkParamsModel::WellWorkParamsModel(const std::vector<std::shared_ptr<ble::src::common::models::WellWorkParams>> data,
    QObject* parent)
    : QAbstractTableModel(parent)
{
    m_data = data;
}

QVariant WellWorkParamsModel::data(const QModelIndex& index, int role) const
{
    auto get_value = [&]() {
        if (m_data.empty())
            return EMPTY_VAL;

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
        case 4:
            return m_data[row_index]->fw;
        }

        return EMPTY_VAL;
    };

    if (role == Qt::DisplayRole) {
        double value = get_value();
        if (is_empty(value))
            return QVariant();

        return QString("%1")
            .arg(value);
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
            return QString("%1").arg("ql");
        case 2:
            return QString("%1").arg("qo");
        case 3:
            return QString("%1").arg("qw");
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
        return true; // ql;
    case 2:
        return true; // qo;
    case 3:
        return true; // qw;
    case 4:
        return false; // fw;
    default:
        return true;
    }
}

bool WellWorkParamsModel::is_empty(double value) const
{
    return std::abs(value - EMPTY_VAL) < 1e-8;
}

}

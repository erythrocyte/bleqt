/*
 * Filename: tauModel.cpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Friday, November 19th 2021, 6:04:27 pm
 * Author: erythrocyte
 *
 * Copyright (c) 2021 Your Company
 */

#include "tauModel.hpp"
#include "common/models/commonVals.hpp"

namespace ble::gui::widgets::models {

TauModel::TauModel(const std::vector<std::shared_ptr<src::common::models::TauData>>& data,
    QObject* parent)
    : QAbstractTableModel(parent)
{
    m_data = data;
    empty_val = src::common::models::CommonVals::EMPTY_VAL;
}

QVariant TauModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        int row_index = index.row(), column_index = index.column();
        double value = get_value(row_index, column_index);
        if (src::common::models::CommonVals::is_empty(value))
            return QVariant();

        return QString("%1")
            .arg(value);
    }

    return QVariant();
}

int TauModel::rowCount(const QModelIndex& parent) const { return m_data.size(); }
int TauModel::columnCount(const QModelIndex& parent) const { return 2; }

QVariant TauModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("%1").arg("T");
        case 1:
            return QString("%1").arg("tau");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

std::tuple<double, double> TauModel::get_value_range(int column_index)
{
    if (m_data.size() == 0)
        return std::make_tuple(empty_val, empty_val);

    double min = 1e8, max = -1e8;

    for (size_t k = 0; k < m_data.size(); k++) {
        double val = get_value(column_index, k);
        if (val < min)
            min = val;
        if (val > max)
            max = val;
    }

    return std::make_tuple(min, max);
}

double TauModel::get_value(int column_index, int row_index) const
{
    if (m_data.size() == 0)
        return empty_val;
    switch (column_index) {
    case 0:
        return m_data[row_index]->time;
    case 1:
        return m_data[row_index]->tau;
    }

    return src::common::models::CommonVals::EMPTY_VAL;
}

}
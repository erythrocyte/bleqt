/*
 * Filename: wellWorkParamsModel.cpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Thursday, September 23rd 2021, 11:09:23 pm
 * Author: erythrocyte
 *
 * Copyright (c) 2021 Your Company
 */

#include "wellWorkParamsModel.hpp"
#include "common/models/commonVals.hpp"

namespace ble::gui::widgets::models {

WellWorkParamsModel::WellWorkParamsModel(const std::vector<std::shared_ptr<ble::src::common::models::WellWorkParams>> data,
    QObject* parent)
    : QAbstractTableModel(parent)
{
    m_data = data;
    empty_val = src::common::models::CommonVals::EMPTY_VAL;
}

QVariant WellWorkParamsModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole) {
        double value = get_value(index.column(), index.row());
        if (src::common::models::CommonVals::is_empty(value))
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

std::tuple<double, double> WellWorkParamsModel::get_min_max_q()
{
    if (m_data.size() == 0)
        return std::make_tuple(empty_val, empty_val);

    double min = 1e8, max = -1e8;

    for (size_t k = 0; k < m_data.size(); k++) {
        double qt_max = get_value(1, k); // liquid
        double qt_min = std::min(get_value(2, k), get_value(3, k)); // 2 - oil, 3 - water;
        if (qt_min < min)
            min = qt_min;
        if (qt_max > max)
            max = qt_max;
    }

    return std::make_tuple(min, max);
}

double WellWorkParamsModel::get_value(int column_index, int row_index) const
{
    if (m_data.empty())
        return empty_val;

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

    return empty_val;
}

}

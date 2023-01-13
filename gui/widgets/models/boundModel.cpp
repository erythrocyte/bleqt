/*
 * Filename: boundaryCondResultModel.cpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Monday, September 27th 2021, 7:53:34 am
 * Author: erythrocyte
 *
 * Copyright (c) 2021 Your Company
 */

#include "boundModel.hpp"
#include "common/models/commonVals.hpp"
#include "common/services/dataDistributionService.hpp"

namespace ble::gui::widgets::models {

BoundModel::BoundModel(
    double x0, double x1, int n,
    const std::shared_ptr<src::common::models::BoundCondData> data,
    QObject* parent)
    : QAbstractTableModel(parent)
{
    m_data = data;
    m_n = n;
    m_x0 = x0;
    m_x1 = x1;
    x_values.clear();
    double dx = (m_x1 - m_x0) / (m_n - 1);
    for (int k = 0; k < m_n; k++) {
        x_values.push_back(m_x0 + k * dx);
    }
    empty_val = src::common::models::CommonVals::EMPTY_VAL;
}

QVariant BoundModel::data(const QModelIndex& index, int role) const
{
    auto get_value = [&]() {
        if (m_data == nullptr)
            return empty_val;

        int row_index = index.row(), column_index = index.column();

        switch (column_index) {
        case 0:
            return x_values[row_index];
        case 1: {
            double x = x_values[row_index];
            return src::common::services::DataDistributionService::get_value(x, m_data->fract_shore_s, empty_val);
        }
        }

        return src::common::models::CommonVals::EMPTY_VAL;
    };

    if (role == Qt::DisplayRole) {
        double value = get_value();
        if (src::common::models::CommonVals::is_empty(value))
            return QVariant();

        return QString("%1")
            .arg(value);
    }

    return QVariant();
}

int BoundModel::rowCount(const QModelIndex& parent) const { return m_n; }
int BoundModel::columnCount(const QModelIndex& parent) const { return 2; }

QVariant BoundModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("%1").arg("r/x");
        case 1:
            return QString("%1").arg("s");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

std::tuple<double, double> BoundModel::getValueRange(int column_index)
{
    std::vector<std::shared_ptr<ble::src::common::models::DataDistribution>> data;
    switch (column_index) {
    case 1:
        data = m_data->fract_shore_s;
        break;
    }

    if (data.size() == 0)
        return std::make_tuple(empty_val, empty_val);

    return src::common::services::DataDistributionService::get_range(m_x0, m_x1, data);
}
}

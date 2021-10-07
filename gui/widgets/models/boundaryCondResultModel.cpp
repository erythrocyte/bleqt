/*
 * Filename: boundaryCondResultModel.cpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Monday, September 27th 2021, 7:53:34 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#include "boundaryCondResultModel.hpp"

namespace ble::gui::widgets::models {

BoundaryCondResultModel::BoundaryCondResultModel(
    const std::shared_ptr<src::mesh::models::Grid> grd,
    const std::shared_ptr<src::common::models::BoundCondData> data,
    QObject* parent)
    : QAbstractTableModel(parent)
{
    m_data = data;
    m_grd = grd;
}

QVariant BoundaryCondResultModel::data(const QModelIndex& index, int role) const
{
    auto get_value = [&]() {
        if (m_data == nullptr)
            return EMPTY_VAL;

        int row_index = index.row(), column_index = index.column();

        switch (column_index) {
        case 0:
            return m_grd->cells[row_index]->cntr;
        case 1: {
            double x = m_grd->cells[row_index]->cntr;
            return m_data->get_value(x, EMPTY_VAL);
        }
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

int BoundaryCondResultModel::rowCount(const QModelIndex& parent) const { return m_grd->cells.size(); }
int BoundaryCondResultModel::columnCount(const QModelIndex& parent) const { return 2; }

QVariant BoundaryCondResultModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("%1").arg("l");
        case 1:
            return QString("%1").arg("rhs");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

bool BoundaryCondResultModel::is_empty(double value) const
{
    return std::abs(value - EMPTY_VAL) < 1e-8;
}

std::tuple<double, double> BoundaryCondResultModel::getValueRange()
{
    if (m_data->bound_sources.size() == 0)
        return std::make_tuple(EMPTY_VAL, EMPTY_VAL);

    double minx_grd, maxx_grd;
    std::tie(minx_grd, maxx_grd) = m_grd->get_min_max();

    return m_data->get_range(minx_grd, maxx_grd);
}

}

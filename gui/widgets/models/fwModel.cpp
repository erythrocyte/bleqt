#include "fwModel.hpp"

#include "common/models/commonVals.hpp"

namespace ble::gui::widgets::models {

FwModel::FwModel(
    const std::vector<std::shared_ptr<src::common::models::FwData>>& data, QObject* parent)
{
    m_data = data;
    empty_val = src::common::models::CommonVals::EMPTY_VAL;
}

QVariant FwModel::data(const QModelIndex& index, int role) const
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

int FwModel::rowCount(const QModelIndex& parent) const { return m_data.size(); };
int FwModel::columnCount(const QModelIndex& parent) const { return 6; };

QVariant FwModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("%1").arg("PV");
        case 1:
            return QString("%1").arg("fw_well");
        case 2:
            return QString("%1").arg("fw_shore");
        case 3:
            return QString("%1").arg("s_num");
        case 4:
            return QString("%1").arg("s_shore");
        case 5:
            return QString("%1").arg("s_balance");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

double FwModel::get_value(int column_index, int row_index) const
{
    if (m_data.size() == 0)
        return empty_val;

    switch (column_index) {
    case 0:
        return m_data[row_index]->pv;
    case 1:
        return m_data[row_index]->fw_num_well;
    case 2:
        return m_data[row_index]->fw_num_shore;
    case 3:
        return m_data[row_index]->sav_num;
    case 4:
        return m_data[row_index]->sav_an_shore;
    case 5:
        return m_data[row_index]->sav_balance;
    default:
        return empty_val;
    }
}

std::tuple<double, double> FwModel::get_value_range(int column_index)
{
    auto calc_range = [&]() {
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
    };

    switch (column_index) {
    case 1:
    case 2:
        return std::make_tuple(0.0, 100.0);
    case 3:
    case 4:
    case 5:
        // return std::make_tuple(0.0, 1.0);
    default:
        return calc_range();
    }
}

}
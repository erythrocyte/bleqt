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
        double value = get_value(index.row(), index.column());
        if (src::common::models::CommonVals::is_empty(value))
            return QVariant();

        return QString("%1")
            .arg(value);
    }

    return QVariant();
}

int FwModel::rowCount(const QModelIndex& parent) const { return m_data.size(); };
int FwModel::columnCount(const QModelIndex& parent) const { return 5; };

QVariant FwModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("%1").arg("t");
        case 1:
            return QString("%1").arg("fw_num");
        case 2:
            return QString("%1").arg("fw_an");
        case 3:
            return QString("%1").arg("s_num");
        case 4:
            return QString("%1").arg("s_an");
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
        return m_data[row_index]->t;
    case 1:
        return m_data[row_index]->fw_num;
    case 2:
        return m_data[row_index]->fw_an;
    case 3:
        return m_data[row_index]->sav_num;
    case 4:
        return m_data[row_index]->sav_an;
    default:
        return empty_val;
    }
}

}
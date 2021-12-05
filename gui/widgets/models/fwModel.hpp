#ifndef BLE_GUI_WIDGETS_MODELS_FWMODEL_H_
#define BLE_GUI_WIDGETS_MODELS_FWMODEL_H_

#include <iostream>
#include <memory>
#include <vector>
#include <tuple>

#include <QAbstractTableModel>

#include "common/models/fwData.hpp"

namespace ble::gui::widgets::models {

class FwModel : public QAbstractTableModel {
    Q_OBJECT

public:
    FwModel(
        const std::vector<std::shared_ptr<src::common::models::FwData>>& data,
        QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<std::shared_ptr<src::common::models::FwData>> m_data;
    double empty_val;

    double get_value(int column_index, int row_index) const;

};

}

#endif
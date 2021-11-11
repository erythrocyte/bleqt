/*
 * Filename: boundaryCondResultModel.hpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Monday, September 27th 2021, 7:49:00 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_MODELS_TOPBOTBOUNDMODEL_H_
#define BLE_GUI_WIDGETS_MODELS_TOPBOTBOUNDMODEL_H_

#include <memory>
#include <tuple>
#include <vector>

#include <QAbstractTableModel>

#include "common/models/boundCondData.hpp"
#include "common/models/dataDistribution.hpp"
#include "mesh/models/grid.hpp"

namespace ble::gui::widgets::models {

class TopBotBoundModel : public QAbstractTableModel {
    Q_OBJECT

public:
    TopBotBoundModel(
        const std::shared_ptr<src::mesh::models::Grid> grd,
        const std::shared_ptr<src::common::models::BoundCondData> data,
        QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    std::tuple<double, double> getValueRange(int column_index);

private:
    std::shared_ptr<src::common::models::BoundCondData> m_data;
    std::shared_ptr<src::mesh::models::Grid> m_grd;
    double empty_val;
};

}

#endif

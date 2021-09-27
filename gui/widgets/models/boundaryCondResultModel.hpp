/*
 * Filename: boundaryCondResultModel.hpp
 * Path: bleqt/gui/widgets/models
 * Created Date: Monday, September 27th 2021, 7:49:00 am
 * Author: erythrocyte
 * 
 * Copyright (c) 2021 Your Company
 */

#ifndef BLE_GUI_WIDGETS_MODELS_BOUNDARYCONDRESULTMODEL_H_
#define BLE_GUI_WIDGETS_MODELS_BOUNDARYCONDRESULTMODEL_H_

#include <memory>
#include <vector>

#include <QAbstractTableModel>

#include "common/models/boundSourceCond.hpp"
#include "mesh/models/grid.hpp"

namespace ble::gui::widgets::models {

class BoundaryCondResultModel : public QAbstractTableModel {
    Q_OBJECT

public:
    BoundaryCondResultModel(
        const std::shared_ptr<src::mesh::models::Grid> grd,
        const std::vector<std::shared_ptr<src::common::models::BoundSourceCond>> data,
        QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    std::vector<std::shared_ptr<src::common::models::BoundSourceCond>> m_data;
    std::shared_ptr<src::mesh::models::Grid> m_grd;
    const double EMPTY_VAL = -99999.0;

    bool is_empty(double value) const;
};

}

#endif

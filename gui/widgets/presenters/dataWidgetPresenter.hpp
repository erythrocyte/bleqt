#ifndef BLE_GUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_
#define BLE_GUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
// #include "conditionsWidgetPresenter.hpp"
// #include "common/models/boundCondData.hpp"
#include "common/models/data.hpp"
#include "dataWidget.hpp"
// #include "gridSettsWidgetPresenter.hpp"
// #include "modelDataWidgetPresenter.hpp"
// #include "relPermDataWidgetPresenter.hpp"
// #include "satSolverSettsWidgetPresenter.hpp"
// #include "shockFrontSettsWidgetPresenter.hpp"
// #include "geomDataWidgetPresenter.hpp"
// #include "geologyDataWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

class DataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    DataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<DataWidget> view);

    std::shared_ptr<ble::src::common::models::Data> get_data();
    std::shared_ptr<DataWidget> get_view();

    // void set_show_shockfront_status(bool status);
    // void set_shockfront_value(double value);

signals:
    // void showShockFrontCurve(bool status);
    void rpValuesUpdated();
    // void update_rhs();
    // void cellCountChanged();

private:
    // std::shared_ptr<GridSettsWidgetPresenter> m_gridset_presenter;
    // std::shared_ptr<ModelDataWidgetPresenter> m_modeldata_presenter;
    // std::shared_ptr<RelPermDataWidgetPresenter> m_relperm_presenter;
    // // std::shared_ptr<SatSolverSettsWidgetPresenter> m_satsolverset_presenter;
    // // std::shared_ptr<ShockFrontSettsWidgetPresenter> m_shockfront_presenter;
    // // std::shared_ptr<ConditionsWidgetPresenter> m_cond_presenter;
    // std::shared_ptr<GeomDataWidgetPresenter> m_geom_presenter;
    // std::shared_ptr<GeologyDataWidgetPresenter> m_geol_presenter;


    void set_widgets_to_view();
    void resolve_sub_presenters();
    void set_signals();

private slots:
    // void onShowShockFrontCurve(bool status) { emit showShockFrontCurve(status); }
    // void onUpdateShockFrontValue(double value);
    void onRpValuesChanged() { emit rpValuesUpdated(); }
    // void onUpdateRhs() { emit update_rhs(); }
    // void onCellCountChanged() { emit cellCountChanged(); }
};

}

#endif
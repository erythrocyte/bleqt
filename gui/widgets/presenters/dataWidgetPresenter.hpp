#ifndef BLEGUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_
#define BLEGUI_WIDGETS_PRESENTERS_DATAWIDGETPRESENTER_H_

#include <iostream>
#include <memory>

#include "Hypodermic/Hypodermic.h"

#include "blePresenter.hpp"
#include "dataWidget.hpp"
#include "gridSettsWidgetPresenter.hpp"
#include "inputData.hpp"
#include "modelDataWidgetPresenter.hpp"
#include "relPermDataWidgetPresenter.hpp"
#include "satSolverSettsWidgetPresenter.hpp"
#include "shockFrontSettsWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

class DataWidgetPresenter : public mvp::BlePresenter {
    Q_OBJECT
public:
    DataWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
        std::shared_ptr<DataWidget> view);

    std::shared_ptr<ble_src::InputData> get_input_data();
    void set_show_shockfront_status(bool status);
    std::shared_ptr<DataWidget> get_view();

signals:
    void showShockFrontCurve(bool status);

private:
    std::shared_ptr<GridSettsWidgetPresenter> m_gridset_presenter;
    std::shared_ptr<ModelDataWidgetPresenter> m_modeldata_presenter;
    std::shared_ptr<RelPermDataWidgetPresenter> m_relperm_presenter;
    std::shared_ptr<SatSolverSettsWidgetPresenter> m_satsolverset_presenter;
    std::shared_ptr<ShockFrontSettsWidgetPresenter> m_shockfront_presenter;

    void set_widgets_to_view();
    void resolve_sub_presenters();
    void set_signals();

private slots:
    void onShowShockFrontCurve(bool status) { emit showShockFrontCurve(status); }
};

}

#endif
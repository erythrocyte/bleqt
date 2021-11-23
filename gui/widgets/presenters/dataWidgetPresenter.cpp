#include "dataWidgetPresenter.hpp"

#include <memory>

#include "models/dataComponents.hpp"

namespace ble::gui::widgets::presenters {

DataWidgetPresenter::DataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DataWidget> view)
    : BlePresenter(container, view)
{
    resolve_sub_presenters();
    set_widgets_to_view();
    set_signals();
}

void DataWidgetPresenter::resolve_sub_presenters()
{
    // m_gridset_presenter = m_container->resolve<GridSettsWidgetPresenter>();
    m_modeldata_presenter = m_container->resolve<ModelDataWidgetPresenter>();
    m_relperm_presenter = m_container->resolve<RelPermDataWidgetPresenter>();
    // m_satsolverset_presenter = m_container->resolve<SatSolverSettsWidgetPresenter>();
    // m_shockfront_presenter = m_container->resolve<ShockFrontSettsWidgetPresenter>();
    // m_cond_presenter = m_container->resolve<ConditionsWidgetPresenter>();
    m_geom_presenter = m_container->resolve<GeomDataWidgetPresenter>();
    m_geol_presenter = m_container->resolve<GeologyDataWidgetPresenter>();
}

void DataWidgetPresenter::set_widgets_to_view()
{
    auto model = std::make_shared<models::DataComponents>();
    // model->gridset_widget = m_gridset_presenter->get_view();
    model->modeldata_widget = m_modeldata_presenter->get_view();
    model->relperm_widget = m_relperm_presenter->get_view();
    // model->satsolverset_view = m_satsolverset_presenter->get_view();
    // model->shockfront_widget = m_shockfront_presenter->get_view();
    // model->cond_widget = m_cond_presenter->get_view();
    model->geom_widget = m_geom_presenter->get_view();
    model->geol_widget = m_geol_presenter->get_view();

    get_view()->set_view_objects(model);
}

void DataWidgetPresenter::set_signals()
{
    // auto success = QObject::connect(m_shockfront_presenter.get(), SIGNAL(showShockFrontCurve(bool)),
    //     this, SLOT(onShowShockFrontCurve(bool)));
    // Q_ASSERT(success);
    auto success = QObject::connect(m_relperm_presenter.get(), SIGNAL(valuesChanged()),
        this, SLOT(onRpValuesChanged()));
    Q_ASSERT(success);
    // success = QObject::connect(m_cond_presenter.get(), SIGNAL(rhsUpdate()),
    //     this, SLOT(onUpdateRhs()));
    // Q_ASSERT(success);
    // success = QObject::connect(m_gridset_presenter.get(), SIGNAL(cellCountChanged()),
    //     this, SLOT(onCellCountChanged()));
    // Q_ASSERT(success);    
}

std::shared_ptr<ble::src::common::models::InputData> DataWidgetPresenter::get_input_data()
{
    auto result = std::make_shared<ble::src::common::models::InputData>();
    // result->grd->type = ble::src::common::models::GridType::TypeEnum::kRegular;
    // result->satSetts->type = ble::src::calc::models::SaturSolverType::kExplicit;

    // result->model->period = m_modeldata_presenter->get_modeling_period();
    // result->model->save_field_step = m_modeldata_presenter->get_save_fields_step();

    // result->phys->kmu = m_relperm_presenter->get_kmu();
    // result->phys->n_oil = m_relperm_presenter->get_n();
    // result->phys->n_wat = m_relperm_presenter->get_n();

    // result->satSetts->cur_val = m_satsolverset_presenter->get_curant_value();
    // result->satSetts->pN = m_satsolverset_presenter->get_press_recalc_n();
    // result->satSetts->need_satur_solve = m_satsolverset_presenter->need_satur_solve();

    // result->grd->rw = m_gridset_presenter->get_well_radius();
    // result->grd->rc = 1.0;
    // result->grd->n = m_gridset_presenter->get_cell_count();
    // result->grd->type = m_gridset_presenter->get_grid_type();

    // result->bound = m_cond_presenter->get_bound_data(result->grd->rw, result->grd->rc);

    return result;
}

std::shared_ptr<DataWidget> DataWidgetPresenter::get_view()
{
    return std::static_pointer_cast<DataWidget>(m_view);
}

// void DataWidgetPresenter::set_show_shockfront_status(bool status)
// {
//     m_shockfront_presenter->set_show_shockfront_status(status);
// }

// void DataWidgetPresenter::set_shockfront_value(double value)
// {
//     m_shockfront_presenter->set_shockfront_value(value);
// }

// void DataWidgetPresenter::onUpdateShockFrontValue(double value)
// {
//     m_shockfront_presenter->set_shockfront_value(value);
// }

}

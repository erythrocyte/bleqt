#include "dataWidgetPresenter.hpp"

#include <memory>

#include "models/dataWidgetComponentsDto.hpp"

namespace ble_gui::widgets::presenters {

DataWidgetPresenter::DataWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<DataWidget> view)
    : BlePresenter(container, view)
{
    resolve_sub_presenters();
    set_widgets_to_view();
}

void DataWidgetPresenter::resolve_sub_presenters()
{
    m_gridset_presenter = m_container->resolve<GridSettsWidgetPresenter>();
    m_modeldata_presenter = m_container->resolve<ModelDataWidgetPresenter>();
}

void DataWidgetPresenter::set_widgets_to_view()
{
    auto gridset_view = std::static_pointer_cast<widgets::GridSettsWidget>(m_gridset_presenter->get_view());
    auto modeldata_view = std::static_pointer_cast<widgets::ModelDataWidget>(m_modeldata_presenter->get_view());

    auto model = std::make_shared<models::DataWidgetComponentsDto>();
    model->gridset_view = gridset_view;
    model->modeldata_view = modeldata_view;

    auto view = std::static_pointer_cast<widgets::DataWidget>(m_view);
    view->set_view_objects(model);
}

}
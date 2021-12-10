#include "fwVisualWidgetPresenter.hpp"

namespace ble::gui::widgets::presenters {

FwVisualWidgetPresenter::FwVisualWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<FwVisualWidget> view)
    : BlePresenter(container, view)
{
}

FwVisualWidgetPresenter::~FwVisualWidgetPresenter()
{
    delete m_model;
}

void FwVisualWidgetPresenter::set_data(const std::vector<std::shared_ptr<src::common::models::FwData>>& data)
{
    m_model = new models::FwModel(data);
    get_view()->set_data(m_model);
}

std::shared_ptr<FwVisualWidget> FwVisualWidgetPresenter::get_view()
{
    return std::static_pointer_cast<FwVisualWidget>(m_view);
}

}

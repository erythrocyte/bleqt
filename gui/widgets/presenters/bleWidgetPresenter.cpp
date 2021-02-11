#include "bleWidgetPresenter.hpp"

namespace ble_gui::widgets::presenters {

BleWidgetPresenter::BleWidgetPresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<QWidget> view)
{
    m_container = container;
    m_view = view;
}

BleWidgetPresenter::~BleWidgetPresenter() { }

}
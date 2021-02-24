#include "blePresenter.hpp"

namespace ble_gui::mvp {

BlePresenter::BlePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<QWidget> view)
{
    m_container = container;
    m_view = view;
}

BlePresenter::~BlePresenter() { }

}

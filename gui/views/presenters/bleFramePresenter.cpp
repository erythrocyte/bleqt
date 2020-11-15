#include "bleFramePresenter.hpp"

ble_gui::views::presenters::BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<IBleFrame> view)
{
    view->run();
}
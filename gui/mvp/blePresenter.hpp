#ifndef BLE_GUI_MVP_BLEPRESENTER_H_
#define BLE_GUI_MVP_BLEPRESENTER_H_

#include <iostream>
#include <memory>

#include <QWidget>

#include "Hypodermic/Hypodermic.h"

namespace ble::gui::mvp {

class BlePresenter : public QObject {
    Q_OBJECT
public:
    BlePresenter(std::shared_ptr<Hypodermic::Container> container, std::shared_ptr<QWidget> view);
    virtual ~BlePresenter() = 0;

protected:
    std::shared_ptr<Hypodermic::Container> m_container;
    std::shared_ptr<QWidget> m_view;
};

}

#endif

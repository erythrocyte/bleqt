#include "bleapp.hpp"

#include <QApplication>
#include <QWidget>

#include "bleFrame.hpp"
#include "bleFramePresenter.hpp"
#include "dataWidgetPresenter.hpp"
#include "fluidParamGraphWidgetPresenter.hpp"
#include "gridSettsWidgetPresenter.hpp"
#include "modelDataWidget.hpp"
#include "relPermDataWidgetPresenter.hpp"
#include "resultDataWidgetPresenter.hpp"
#include "satSolverSettsWidgetPresenter.hpp"
#include "shockFrontSettsWidgetPresenter.hpp"
#include "boundaryConditionsWidgetPresenter.hpp"
#include "boundaryCondResultWidgetPresenter.hpp"

namespace ble::gui {

BleApplication::BleApplication()
{
    Hypodermic::ContainerBuilder builder;

    builder.registerType<views::BleFrame>();
    builder.registerType<views::presenters::BleFramePresenter>();
    builder.registerType<widgets::FluidParamsGraphWidget>();
    builder.registerType<widgets::presenters::FluidParamGraphWidgetPresenter>();
    builder.registerType<widgets::DataWidget>();
    builder.registerType<widgets::presenters::DataWidgetPresenter>();
    builder.registerType<widgets::ResultDataWidget>();
    builder.registerType<widgets::presenters::ResultDataWidgetPresenter>();
    builder.registerType<widgets::presenters::GridSettsWidgetPresenter>();
    builder.registerType<widgets::presenters::ModelDataWidgetPresenter>();
    builder.registerType<widgets::presenters::RelPermDataWidgetPresenter>();
    builder.registerType<widgets::presenters::SatSolverSettsWidgetPresenter>();
    builder.registerType<widgets::presenters::ShockFrontSettsWidgetPresenter>();
    builder.registerType<widgets::presenters::BoundaryConditionsWidgetPresenter>();
    builder.registerType<widgets::presenters::BoundaryCondResultWidgetPresenter>();

    m_container = builder.build();
}

BleApplication::~BleApplication()
{
}

void BleApplication::run(int argc, char** argv)
{
    QApplication qapp(argc, argv);

    auto mainPresenter = m_container->resolve<views::presenters::BleFramePresenter>();
    mainPresenter->run();

    qapp.exec();
}

}

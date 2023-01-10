#include "bleapp.hpp"

#include <QApplication>
#include <QWidget>

#include "bleFrame.hpp"
#include "bleFramePresenter.hpp"
#include "boundVisualWidgetPresenter.hpp"
#include "conditionsWidgetPresenter.hpp"
#include "dataWidgetPresenter.hpp"
#include "fluidParamGraphWidgetPresenter.hpp"
#include "gridSettsWidgetPresenter.hpp"
#include "resultDataWidgetPresenter.hpp"
#include "satSolverSettsWidgetPresenter.hpp"
#include "shockFrontSettsWidgetPresenter.hpp"
#include "widgets/schemeWidget.hpp"

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
    builder.registerType<widgets::presenters::SatSolverSettsWidgetPresenter>();
    builder.registerType<widgets::presenters::ShockFrontSettsWidgetPresenter>();
    builder.registerType<widgets::presenters::ConditionsWidgetPresenter>();
    builder.registerType<widgets::presenters::BoundVisualWidgetPresenter>();
    builder.registerType<widgets::SchemeWidget>();

    m_container = builder.build();
}

BleApplication::~BleApplication()
{
}

void BleApplication::run(int argc, char** argv)
{
    QApplication qapp(argc, argv);

    // Q_INIT_RESOURCE(resources);

    auto mainPresenter = m_container->resolve<views::presenters::BleFramePresenter>();
    mainPresenter->run();

    qapp.exec();

    // Q_CLEANUP_RESOURCE(resources);
}

}

#include "bleFramePresenter.hpp"

#include <chrono>
#include <iomanip>

#include <QFileSystemWatcher>

#include "bleCalc.hpp"
#include "dataWidget.hpp"
#include "file/services/workFile.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "logging/logger.hpp"
#include "makeGrid.hpp"
#include "shockFront.hpp"
#include "workString.hpp"

namespace ble_gui::views::presenters {

BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BleFrame> view)
    : BlePresenter(container, view)
{
    init_log();

    m_fluidWidgetPresenter = m_container->resolve<bwp::FluidParamGraphWidgetPresenter>();
    auto fluidParamsWidget = std::static_pointer_cast<widgets::FluidParamsGraphWidget>(m_fluidWidgetPresenter->get_view());

    m_resultDataWidgetPresenter = m_container->resolve<bwp::ResultDataWidgetPresenter>();
    auto resultDataWidget = std::static_pointer_cast<widgets::ResultDataWidget>(m_resultDataWidgetPresenter->get_view());

    m_dataWidgetPresenter = m_container->resolve<bwp::DataWidgetPresenter>();
    auto dataWidgetView = std::static_pointer_cast<widgets::DataWidget>(m_dataWidgetPresenter->get_view());

    std::static_pointer_cast<BleFrame>(m_view)->set_widgets(fluidParamsWidget, resultDataWidget, dataWidgetView);

    set_signals();
    m_dataWidgetPresenter->set_show_shockfront_status(true);
    onRpValuesUpdated();
}

void BleFramePresenter::run()
{
    std::static_pointer_cast<BleFrame>(m_view)->run();
}

void BleFramePresenter::set_signals()
{
    auto success = QObject::connect(m_dataWidgetPresenter.get(), SIGNAL(showShockFrontCurve(bool)),
        this, SLOT(onShowShockFrontCurve(bool)));
    Q_ASSERT(success);

    success = QObject::connect(m_dataWidgetPresenter.get(), SIGNAL(rpValuesUpdated()),
        this, SLOT(onRpValuesUpdated()));
    Q_ASSERT(success);

    QObject* view_obj = dynamic_cast<QObject*>(m_view.get());
    success = QObject::connect(view_obj, SIGNAL(sgn_run_calc()), this, SLOT(on_run_calc()));
    Q_ASSERT(success);
}

void BleFramePresenter::onShowShockFrontCurve(bool status)
{
    m_resultDataWidgetPresenter->set_sc_visibility(status);
    if (status) {
        auto data = m_dataWidgetPresenter->get_input_data();
        double sc = ble_src::get_shock_front(data->phys);
        m_resultDataWidgetPresenter->update_sc(data->grd->l, sc);
    }
}

void BleFramePresenter::onRpValuesUpdated()
{
    auto data = m_dataWidgetPresenter->get_input_data();
    double sc = ble_src::get_shock_front(data->phys);
    m_dataWidgetPresenter->set_shockfront_value(sc);
    m_resultDataWidgetPresenter->update_sc(data->grd->l, sc);
    m_fluidWidgetPresenter->update_view(data->phys, sc);
}

void BleFramePresenter::on_run_calc()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto data = m_dataWidgetPresenter->get_input_data();
    auto grd = ble_src::make_grid(data);

    set_status(tr("calculation running"));

    std::function<void(int)> a = std::bind(&BleFramePresenter::update_progress, this, std::placeholders::_1);
    auto solver = std::make_shared<ble_src::BleCalc>();
    solver->calc(grd, data, a);
    auto results = solver->get_result();
    results->grd = grd;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::string mess = ble_src::string_format("calculation completed in %.2f sec.", diff.count());
    set_status(QString::fromStdString(mess));

    m_resultDataWidgetPresenter->set_data(results, a);
    update_progress(100);
}

std::shared_ptr<BleFrame> BleFramePresenter::get_view()
{
    return std::static_pointer_cast<BleFrame>(m_view);
}

void BleFramePresenter::init_log()
{
    std::string fn = "app.log";
    ble_src::logging::init_log(fn);
    QFileSystemWatcher* watcher = new QFileSystemWatcher();
    watcher->addPath(QString::fromStdString(fn));

    auto success = QObject::connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(handleFileChanged(QString)));
    Q_ASSERT(success);

    ble_src::logging::write_log("test1", ble_src::logging::kError);
}

void BleFramePresenter::handleFileChanged(QString str)
{
    auto last_line = ble_src::file::services::get_last_line(str.toStdString());
    std::string mess;
    ble_src::logging::SeverityLevelEnum level;
    std::tie(mess, level) = parse_log_mess("3");
    get_view()->add_log_message(mess, level);
}

std::tuple<std::string, ble_src::logging::SeverityLevelEnum> BleFramePresenter::parse_log_mess(std::string mess)
{
    auto level = ble_src::logging::SeverityLevelEnum::kError;
    return std::make_tuple<std::string, ble_src::logging::SeverityLevelEnum>(std::move(mess), std::move(level));
}

}

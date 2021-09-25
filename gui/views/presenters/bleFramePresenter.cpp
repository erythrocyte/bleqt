#include "bleFramePresenter.hpp"

#include <chrono>
#include <iomanip>

#include <QFileSystemWatcher>

#include "calc/models/bleCalc.hpp"
#include "common/services/shockFront.hpp"
#include "common/services/workString.hpp"
#include "dataWidget.hpp"
#include "file/services/workFile.hpp"
#include "fluidParamsGraphWidget.hpp"
#include "logging/logger.hpp"
#include "mesh/models/grid.hpp"
#include "mesh/services/makeGrid.hpp"

namespace cs = ble::src::common::services;

namespace ble::gui::views::presenters {

BleFramePresenter::BleFramePresenter(std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<BleFrame> view)
    : BlePresenter(container, view)
{
    m_log_line_start_index = 0;
    init_log();

    m_fluidWidgetPresenter = m_container->resolve<bwp::FluidParamGraphWidgetPresenter>();
    auto fluidParamsWidget = std::static_pointer_cast<widgets::FluidParamsGraphWidget>(m_fluidWidgetPresenter->get_view());

    m_resultDataWidgetPresenter = m_container->resolve<bwp::ResultDataWidgetPresenter>();
    auto resultDataWidget = std::static_pointer_cast<widgets::ResultDataWidget>(m_resultDataWidgetPresenter->get_view());

    m_dataWidgetPresenter = m_container->resolve<bwp::DataWidgetPresenter>();
    auto dataWidgetView = std::static_pointer_cast<widgets::DataWidget>(m_dataWidgetPresenter->get_view());

    m_wellWorkDataWidgetPresenter = m_container->resolve<bwp::WellWorkDataWidgetPresenter>();
    auto wellWorkDataView = std::static_pointer_cast<widgets::WellWorkDataWidget>(m_wellWorkDataWidgetPresenter->get_view());

    std::static_pointer_cast<BleFrame>(m_view)->set_widgets(fluidParamsWidget, resultDataWidget, dataWidgetView, wellWorkDataView);

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
        double sc = cs::shock_front::get_shock_front(data->phys);
        m_resultDataWidgetPresenter->update_sc(data->grd->l, sc);
    }
}

void BleFramePresenter::onRpValuesUpdated()
{
    auto data = m_dataWidgetPresenter->get_input_data();
    double sc = cs::shock_front::get_shock_front(data->phys);
    m_dataWidgetPresenter->set_shockfront_value(sc);
    m_resultDataWidgetPresenter->update_sc(data->grd->l, sc);
    m_fluidWidgetPresenter->update_view(data->phys, sc);
}

void BleFramePresenter::on_run_calc()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto data = m_dataWidgetPresenter->get_input_data();
    auto grd = ble::src::mesh::services::make_grid(data);

    set_status(tr("calculation running"));

    std::function<void(int)> a = std::bind(&BleFramePresenter::update_progress, this, std::placeholders::_1);
    auto solver = std::make_shared<src::calc::models::BleCalc>();
    solver->calc(grd, data, a);
    auto results = solver->get_result();
    results->grd = grd;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::string mess = cs::string_format("calculation completed in %.2f sec.", diff.count());
    set_status(QString::fromStdString(mess));

    m_resultDataWidgetPresenter->set_data(results, a);
    m_wellWorkDataWidgetPresenter->set_data(solver->get_well_work_params());
    m_wellWorkDataWidgetPresenter->set_time_period(data->model->period);
    update_progress(100);
}

std::shared_ptr<BleFrame> BleFramePresenter::get_view()
{
    return std::static_pointer_cast<BleFrame>(m_view);
}

void BleFramePresenter::init_log()
{
    std::string fn = "app.log";
    ble::src::logging::init_log(fn);
    QFileSystemWatcher* watcher = new QFileSystemWatcher();
    auto success = QObject::connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(handleFileChanged(QString)));
    Q_ASSERT(success);
    watcher->addPath(QString::fromStdString(fn));
}

void BleFramePresenter::handleFileChanged(QString str)
{
    auto is_level_suit = [](ble::src::logging::SeverityLevelEnum lvl) {
        return lvl == ble::src::logging::kWarning || lvl == ble::src::logging::kInfo || lvl == ble::src::logging::kError
            ? true
            : false;
    };
    auto lines = ble::src::file::services::read_file_from_line(m_log_line_start_index, str.toStdString());
    m_log_line_start_index += lines.size();
    std::string mess;
    ble::src::logging::SeverityLevelEnum level;
    for (auto& line : lines) {
        std::tie(mess, level) = parse_log_mess(line);
        if (is_level_suit(level)) {
            get_view()->add_log_message(mess, level);
        }
    }
}

std::tuple<std::string, ble::src::logging::SeverityLevelEnum> BleFramePresenter::parse_log_mess(std::string mess)
{
    auto get_time = [](const std::string mess) {
        std::vector<std::string> a = ble::src::common::services::split(mess, " ");
        std::string v = a[0].substr(1);
        std::string v2 = a[1].substr(0, a[1].size() - 1);
        return ble::src::common::services::string_format("%s %s", v.c_str(), v2.c_str());
    };

    auto get_level = [](const std::string mess) {
        std::vector<std::string> a = ble::src::common::services::split(mess, " ");
        std::string lvl = a[3].substr(1, a[3].size() - 2);
        if (lvl == "error") {
            return ble::src::logging::kError;
        } else if (lvl == "warning") {
            return ble::src::logging::kWarning;
        } else if (lvl == "fatal") {
            return ble::src::logging::kFatal;
        } else if (lvl == "trace") {
            return ble::src::logging::kTrace;
        } else if (lvl == "debug") {
            return ble::src::logging::kDebug;
        } else {
            return ble::src::logging::kInfo;
        }
    };
    auto get_message = [](const std::string mess) {
        size_t pos = mess.find_last_of("]");
        return mess.substr(pos + 1, mess.length() - pos + 1);
    };

    std::string time = get_time(mess);
    ble::src::logging::SeverityLevelEnum level = get_level(mess);
    std::string mm = get_message(mess);
    std::string pp = ble::src::common::services::string_format("%s - %s", time.c_str(), mm.c_str());
    return std::make_tuple<std::string, ble::src::logging::SeverityLevelEnum>(std::move(pp), std::move(level));
}

}

#include "fluidParamGraphWidgetPresenter.hpp"

#include <memory>

#include "common/services/commonMath.hpp"
#include "common/services/workRp.hpp"

namespace cs = ble::src::common::services;

namespace ble::gui::widgets::presenters {

FluidParamGraphWidgetPresenter::FluidParamGraphWidgetPresenter(
    std::shared_ptr<Hypodermic::Container> container,
    std::shared_ptr<FluidParamsGraphWidget> view)
    : BlePresenter(container, view)
{
    QObject* view_obj = dynamic_cast<QObject*>(view.get());
    const bool connected = connect(view_obj,
        SIGNAL(get_data(const std::shared_ptr<ble::src::common::models::PhysData>, double)),
        this,
        SLOT(send_data(const std::shared_ptr<ble::src::common::models::PhysData>, double)));
    Q_ASSERT(connected);
}

std::shared_ptr<models::FluidParamsDto> FluidParamGraphWidgetPresenter::send_data(
    const std::shared_ptr<ble::src::common::models::PhysData> data, double sc)
{
    auto result = std::make_shared<models::FluidParamsDto>();

    int n = 200; // point count;
    double ds = 1.0 / (n - 1); // step;

    result->max_dfbl = 1.0;

    double dsc = cs::rp::get_fbl(sc, data);

    for (int k = 0; k < n; k++) {
        double s = ds * k; // saturation;
        double kw = cs::rp::get_kw(s, data);
        double koil = cs::rp::get_koil(s, data);
        double fbl = cs::rp::get_fbl(s, data);
        double dfbl = cs::rp::get_dfbl(s, data);

        if (dfbl > result->max_dfbl)
            result->max_dfbl = dfbl;

        result->kws.append(QPointF(s, kw));
        result->koils.append(QPointF(s, koil));
        result->fbls.append(QPointF(s, fbl));
        result->dfbls.append(QPointF(s, dfbl));
    }

    double x_up = ble::src::common::services::get_value_lin_approx(0, 0, dsc, sc, 1.0);
    result->scs.append(QPointF(sc, dsc));
    result->scs.append(QPointF(x_up, 1.));
    result->scs.append(QPointF(0., 0.));
    result->scs.append(QPointF(sc, dsc));
    result->scs.append(QPointF(sc, 0.));

    return result;
}

void FluidParamGraphWidgetPresenter::update_view(
    const std::shared_ptr<ble::src::common::models::PhysData> physData, double sc)
{
    std::static_pointer_cast<widgets::FluidParamsGraphWidget>(m_view)->update_view(physData, sc);
}

std::shared_ptr<FluidParamsGraphWidget> FluidParamGraphWidgetPresenter::get_view()
{
    return std::static_pointer_cast<FluidParamsGraphWidget>(m_view);
}

}

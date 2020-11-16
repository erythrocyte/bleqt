#include "fluidParamsWidget.hpp"

#include "commonMath.hpp"
#include "shockFront.hpp"
#include "workRp.hpp"

ble_gui::widgets::FluidParamsVisualWidget::FluidParamsVisualWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::FluidParams)

{
    ui->setupUI(this);
}

void ble_gui::widgets::FluidParamsVisualWidget::update_view(
    const std::shared_ptr<ble_src::PhysData> physData, double sc)
{
    ui->series_kw->clear();
    ui->series_koil->clear();
    ui->series_fbl->clear();
    ui->series_dfbl->clear();
    ui->series_sc->clear();

    auto data = get_data(physData, sc);

    if (data != nullptr) {
        ui->series_kw->append(data->kws);
        ui->series_koil->append(data->koils);
        ui->series_fbl->append(data->fbls);
        ui->series_dfbl->append(data->dfbls);

        ui->series_sc->append(data->scs);

        ui->axis_dfY->setMax(data->max_dfbl);
    }
}

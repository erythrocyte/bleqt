#include "fluidParamsGraphWidget.hpp"

namespace ble::gui::widgets {

FluidParamsGraphWidget::FluidParamsGraphWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::FluidParams)

{
    ui->setupUI(this);
}

void FluidParamsGraphWidget::update_view(double n, double kmu, double sc)
{
    ui->series_kw->clear();
    ui->series_koil->clear();
    ui->series_fbl->clear();
    ui->series_dfbl->clear();
    ui->series_sc->clear();
    ui->sigma->clear();

    auto data = get_data(n, kmu, sc);

    if (data != nullptr) {
        ui->series_kw->append(data->kws);
        ui->series_koil->append(data->koils);
        ui->series_fbl->append(data->fbls);
        ui->series_dfbl->append(data->dfbls);
        ui->sigma->append(data->sigma);

        ui->series_sc->append(data->scs);

        ui->axis_dfY->setMax(data->max_dfbl);
    }
}

}

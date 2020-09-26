#include "fluidParamsVisualWidget.hpp"

#include "commonMath.hpp"
#include "shockFront.hpp"
#include "workRp.hpp"

#include <QGridLayout>

ble_gui::widgets::FluidParamsVisualWidget::FluidParamsVisualWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::FluidParamsVisual)

{
    ui->setupUI(this);
    setLayout(ui->layout);
}

void ble_gui::widgets::FluidParamsVisualWidget::update_view(const std::shared_ptr<ble_src::PhysData> data,
    double sc)
{

    ui->series_kw->clear();
    ui->series_koil->clear();
    ui->series_fbl->clear();
    ui->series_dfbl->clear();
    ui->series_sc->clear();

    fill_data(data, sc);
}

void ble_gui::widgets::FluidParamsVisualWidget::fill_data(const std::shared_ptr<ble_src::PhysData> data,
    double sc)
{
    int n = 200;
    double ds = 1.0 / (n - 1);

    double max_dfbl = 1.0;

    double dsc = ble_src::get_fbl(sc, data);

    for (int k = 0; k < n; k++) {
        double s = ds * k;
        double kw = ble_src::get_kw(s, data);
        double koil = ble_src::get_koil(s, data);
        double fbl = ble_src::get_fbl(s, data);
        double dfbl = ble_src::get_dfbl(s, data);

        if (dfbl > max_dfbl)
            max_dfbl = dfbl;

        ui->series_kw->append(s, kw);
        ui->series_koil->append(s, koil);
        ui->series_fbl->append(s, fbl);
        ui->series_dfbl->append(s, dfbl);
    }

    double x_up = ble_src::common_math::get_value_lin_approx(0, 0, dsc, sc, 1.0);
    ui->series_sc->append(sc, dsc);
    ui->series_sc->append(x_up, 1.);
    ui->series_sc->append(0., 0.);
    ui->series_sc->append(sc, dsc);
    ui->series_sc->append(sc, 0.);

    ui->axis_dfY->setMax(max_dfbl);
}

#include "fluidParamsGraphWidget.hpp"

#include <QSvgGenerator>

#include "services/saveFilePathService.hpp"

namespace ble::gui::widgets {

FluidParamsGraphWidget::FluidParamsGraphWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::FluidParams)

{
    ui->setupUI(this);

    subscribe();
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

void FluidParamsGraphWidget::subscribe()
{
    auto success = QObject::connect(ui->save_image_svg_action, SIGNAL(triggered()), this, SLOT(handleImageSaveSvg()));
    Q_ASSERT(success);
}

void FluidParamsGraphWidget::handleImageSaveSvg()
{
    // QString filter = "SVG (*.svg)";
    // QString file_path = QFileDialog::getSaveFileName(
    //     this, "Save Image", "/home", filter, &filter);

    // std::cout << "s = " << file_path.toStdString() << "\n";

    QString file_path = services::save_file_path::get_save_file_path_svg(this, "/home");

    if (file_path.isEmpty())
        return;

    QSvgGenerator* svg_generator = new QSvgGenerator();
    svg_generator->setFileName(file_path);
    svg_generator->setSize(QSize(300, 300));
    svg_generator->setViewBox(QRect(0, 0, 200, 200));
    svg_generator->setTitle(tr("SVG Generator Example Drawing"));
    svg_generator->setDescription(tr("An SVG drawing created by the SVG Generator "
                                     "Example provided with Qt."));

    QPainter* painter = new QPainter();
    painter->begin(svg_generator);
    ui->chart_view->render(painter);
    painter->end();

    delete painter;
    delete svg_generator;
}

}

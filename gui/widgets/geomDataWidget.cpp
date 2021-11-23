#include "geomDataWidget.hpp"


namespace ble::gui::widgets {

GeomDataWidget::GeomDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::GeomData)
{
    ui->setupUi(this);

    subscribe();
}

void GeomDataWidget::subscribe()
{
}

void GeomDataWidget::fix_well_radius(const QString& txt)
{
    // auto gridType = scm::GridType::get_enum(txt.toStdString());
    // if (gridType == scm::GridType::kRegular) {
    //     ui->WellRadius->setValue(0.0);
    // } else {
    //     ui->WellRadius->setValue(1e-3);
    // }
}

}
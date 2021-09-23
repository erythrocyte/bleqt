#include "modelDataWidget.hpp"

namespace ble::gui::widgets {
ModelDataWidget::ModelDataWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new UI::ModelData)
{
    ui->setupUi(this);

    auto a = connect(ui->Period, SIGNAL(valueChanged(double)), this, SLOT(modeling_period_changed(double)));
    Q_ASSERT(a);
}

void ModelDataWidget::modeling_period_changed(double value)
{
    ui->SaveFieldSteps->setMaximum(value);
}

}

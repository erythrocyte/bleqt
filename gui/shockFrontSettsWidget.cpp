#include "shockFrontSettsWidget.hpp"

#include <QGroupBox>
#include <QVBoxLayout>

namespace ble_gui
{
    ShockFrontSettsWidget::ShockFrontSettsWidget(QWidget *parent)
    {
		QGroupBox *groupBox = new QGroupBox("Shock front");
		QVBoxLayout *mainLayout = new QVBoxLayout(this);
		mainLayout->addWidget(groupBox);
        QVBoxLayout *layout = new QVBoxLayout(this);
		groupBox->setLayout(layout);

        shockFrontValue = new QLabel("");
        layout->addWidget(shockFrontValue);

        showCurve = new QCheckBox("Show shock front");
        showCurve->setChecked(true);

        layout->addWidget(showCurve);
    }

} // namespace ble_gui

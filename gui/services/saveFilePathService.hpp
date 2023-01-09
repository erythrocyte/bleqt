#ifndef BLE_GUI_SERVICES_SAVEFILEPATHSERVICE_H_
#define BLE_GUI_SERVICES_SAVEFILEPATHSERVICE_H_

#include <QString>
#include <QWidget>
#include <string>

namespace ble::gui::services::save_file_path {

QString get_save_file_path_svg(QWidget* parent, const std::string& home_dir);

}

#endif
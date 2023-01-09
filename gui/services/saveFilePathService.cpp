#include "saveFilePathService.hpp"

#include <QFileDialog>

namespace ble::gui::services::save_file_path {

QString get_save_file_path_svg(QWidget* parent, const std::string& home_dir)
{
    // this does not work for me. It returns file name without extension
    // QString filter = "SVG (*.svg)";
    // QString file_path = QFileDialog::getSaveFileName(
    //     parent, "Save Image", "/home", filter, &filter);

    QString result;
    QString filter = "SVG (*.svg)";
    QFileDialog* dialog = new QFileDialog(parent, "Save Image", QString::fromStdString(home_dir), filter);
    dialog->setDefaultSuffix(".svg");
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    if (dialog->exec()) {
        result = dialog->selectedFiles().front();
    }

    delete dialog;
    return result;
}

}
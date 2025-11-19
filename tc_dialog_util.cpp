//
// Created by RGAA on 19/11/2025.
//

#include "tc_dialog_util.h"
#include <QFileDialog>

namespace tc
{

    QString TcDialogUtil::SelectDirectory(const QString& title, const QString& default_path, QWidget* parent) {
        QString dir = QFileDialog::getExistingDirectory(
                parent,
                title,
                default_path,   // 默认打开的目录
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );

        return dir;
    }

}
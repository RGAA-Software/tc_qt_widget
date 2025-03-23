//
// Created by RGAA on 23/03/2025.
//

#ifndef GAMMARAY_TC_CUSTOM_TITLEBAR_DIALOG_H
#define GAMMARAY_TC_CUSTOM_TITLEBAR_DIALOG_H

#include <QMainWindow>

namespace tc
{

    class NoMarginVLayout;
    class TcCustomTitleBar;

    class TcCustomTitleBarDialog : public QMainWindow {
    public:
        explicit TcCustomTitleBarDialog(const QString& title, QWidget* parent = nullptr);

    protected:
        QWidget* central_widget_ = nullptr;
        NoMarginVLayout* root_layout_ = nullptr;
    };

}
#endif //GAMMARAY_TC_CUSTOM_TITLEBAR_DIALOG_H

//
// Created by RGAA on 23/03/2025.
//

#ifndef GAMMARAY_TC_DIALOG_H
#define GAMMARAY_TC_DIALOG_H

#include "tc_custom_titlebar_dialog.h"

namespace tc
{

    using OnDialogCancelClicked = std::function<void()>;
    using OnDialogSureClicked = std::function<void()>;

    class TcDialog : public TcCustomTitleBarDialog {
    public:
        static TcDialog* Make(const QString& title, const QString& msg, QWidget* parent);
        TcDialog(const QString& title, const QString& msg, QWidget* parent);

        void SetOnDialogSureClicked(OnDialogSureClicked&& cbk);
        void SetOnDialogCancelClicked(OnDialogCancelClicked&& cbk);

    private:
        OnDialogCancelClicked cbk_cancel_;
        OnDialogSureClicked cbk_sure_;

    };
}

#endif //GAMMARAY_TC_DIALOG_H

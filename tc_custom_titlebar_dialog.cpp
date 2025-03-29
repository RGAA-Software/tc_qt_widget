//
// Created by RGAA on 23/03/2025.
//

#include "tc_custom_titlebar_dialog.h"
#include "tc_custom_titlebar.h"
#include "no_margin_layout.h"
#include "tc_qt_widget/tc_pushbutton.h"
#include "tc_qt_widget/widget_helper.h"
#include "tc_qt_widget/tc_custom_titlebar.h"
#include "tc_qt_widget/widgetframe/mainwindow_wrapper.h"

namespace tc
{

    TcCustomTitleBarDialog::TcCustomTitleBarDialog(const QString& title, QWidget* parent) : QMainWindow(parent) {
        setWindowModality(Qt::ApplicationModal);
        setAttribute(Qt::WA_DeleteOnClose);
        setContentsMargins(0, 0, 0, 0);

        title_ = title;
        root_layout_ = new NoMarginVLayout();
        central_widget_ = new QWidget(this);
        central_widget_->setLayout(root_layout_);
        setCentralWidget(central_widget_);

        (new MainWindowWrapper(nullptr, this))
            ->ShowProfile(false)
            ->ShowSettings(false)
            ->ShowPinTop(false)
            ->ShowMin(false)
            ->ShowMax(false)
            ->Setup(title_);
    }

    void TcCustomTitleBarDialog::Show() {
        this->show();
    }
}
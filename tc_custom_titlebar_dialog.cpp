//
// Created by RGAA on 23/03/2025.
//

#include <dwmapi.h>
#include "tc_custom_titlebar_dialog.h"
#include "tc_custom_titlebar.h"
#include "no_margin_layout.h"
#include "tc_qt_widget/tc_pushbutton.h"
#include "tc_qt_widget/widget_helper.h"
#include "tc_qt_widget/tc_custom_titlebar.h"
#include "tc_qt_widget/widgetframe/mainwindow_wrapper.h"

namespace tc
{

    TcCustomTitleBarDialog::TcCustomTitleBarDialog(const QString& title, QWidget* parent) : QDialog(parent) {
        //setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint | Qt::ExpandedClientAreaHint | Qt::NoTitleBarBackgroundHint);
        WidgetHelper::SetTitleBarColor(this);
        setModal(true);
        setContentsMargins(0, 0, 0, 0);
        setWindowTitle(title);

        setAttribute(Qt::WA_ShowModal, true);
        setAttribute(Qt::WA_DeleteOnClose, false);
        setWindowModality(Qt::ApplicationModal);

        root_layout_ = new NoMarginVLayout();
        setLayout(root_layout_);
    }
}
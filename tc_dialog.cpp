//
// Created by RGAA on 23/03/2025.
//

#include "tc_dialog.h"
#include "no_margin_layout.h"
#include "tc_pushbutton.h"
#include "tc_label.h"

namespace tc
{

    TcDialog* TcDialog::Make(const QString& title, const QString& msg, QWidget* parent) {
        auto dlg = new TcDialog(title, msg, parent);
        return dlg;
    }

    TcDialog::TcDialog(const QString& title, const QString& msg, QWidget* parent) : TcCustomTitleBarDialog(title, parent) {
        setWindowTitle(title);
        setFixedSize(410, 220);

        root_layout_->addSpacing(20);
        {
            auto item_layout = new NoMarginHLayout();
            auto lbl_message = new TcLabel(this);
            lbl_message->setText(msg);
            lbl_message->setWordWrap(true);
            lbl_message->setStyleSheet("font-size: 15px;");
            item_layout->addSpacing(29);
            item_layout->addWidget(lbl_message);
            item_layout->addSpacing(29);
            root_layout_->addLayout(item_layout);
        }
        root_layout_->addStretch();
        {
            auto item_layout = new NoMarginHLayout();
            auto btn_size = QSize(90, 28);
            item_layout->addStretch();
            auto btn_cancel = new TcPushButton(this);
            btn_cancel->SetTextId("id_cancel");
            btn_cancel->setProperty("class", "danger");
            btn_cancel->setFixedSize(btn_size);
            item_layout->addWidget(btn_cancel);
            item_layout->addSpacing(20);

            connect(btn_cancel, &QPushButton::clicked, this, [=, this]() {
                if (cbk_cancel_) {
                    cbk_cancel_();
                }
                this->close();
                this->deleteLater();
            });

            auto btn_ok = new TcPushButton(this);
            btn_ok->SetTextId("id_ok");
            btn_ok->setFixedSize(btn_size);
            item_layout->addWidget(btn_ok);
            item_layout->addStretch();

            connect(btn_ok, &QPushButton::clicked, this, [=, this]() {
                if (cbk_sure_) {
                    cbk_sure_();
                }
                this->hide();
                QMetaObject::invokeMethod(this, [=, this]() {
                    this->close();
                    this->deleteLater();
                });
            });

            root_layout_->addLayout(item_layout);
        }
        root_layout_->addSpacing(30);

    }

    void TcDialog::SetOnDialogSureClicked(OnDialogSureClicked&& cbk) {
        cbk_sure_ = cbk;
    }

    void TcDialog::SetOnDialogCancelClicked(OnDialogCancelClicked&& cbk) {
        cbk_cancel_ = cbk;
    }

}
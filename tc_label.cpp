//
// Created by RGAA on 22/03/2025.
//

#include "tc_label.h"

namespace tc
{

    TcLabel::TcLabel(QWidget* parent) : QLabel(parent), TcTranslator(this) {

    }

    TcLabel::~TcLabel() {

    }

    void TcLabel::SetTextId(const QString& id) {
        if (id.isEmpty()) {
            return;
        }
        TcTranslator::SetTextId(id);
        this->setText(tcTr(text_id_));
    }

    void TcLabel::OnTranslate(LanguageKind kind) {
        TcTranslator::OnTranslate(kind);
        if (text_id_.isEmpty()) {
            return;
        }
        this->setText(tcTr(text_id_));
    }

}
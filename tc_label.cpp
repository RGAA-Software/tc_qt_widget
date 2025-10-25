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

    void TcLabel::enterEvent(QEnterEvent *event) {
        enter_ = true;
        repaint();
        if (listener_) {
            cursor_ = cursor();
            setCursor(Qt::PointingHandCursor);
        }
    }

    void TcLabel::leaveEvent(QEvent *event) {
        enter_ = false;
        repaint();
        if (listener_) {
            setCursor(cursor_);
        }
    }

    void TcLabel::mousePressEvent(QMouseEvent *ev) {
        pressed_ = true;
        repaint();
    }

    void TcLabel::mouseReleaseEvent(QMouseEvent *ev) {
        pressed_ = false;
        repaint();
        if (listener_) {
            listener_(this);
        }
    }

    void TcLabel::SetOnClickListener(OnClickListener&& listener) {
        listener_ = listener;
    }

}
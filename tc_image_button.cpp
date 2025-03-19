//
// Created by RGAA on 19/03/2025.
//

#include "tc_image_button.h"

namespace tc
{

    TcImageButton::TcImageButton(const QString& uri, const QSize& scale_size, QWidget* parent) : QWidget(parent) {
        pixmap_ = QPixmap::fromImage(QImage(uri));
        if (scale_size.width() > 0 && scale_size.height() > 0) {
            pixmap_ = pixmap_.scaled(scale_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }

    void TcImageButton::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);

        int color = 0xffffff;
        if (pressed_) {
            color = 0xdddddd;
        }
        else if (enter_) {
            color = 0xeeeeee;
        }
        painter.setBrush(QBrush(color));
        painter.drawRoundedRect(this->rect(), 4, 4);

        painter.setRenderHint(QPainter::Antialiasing, true);
        if (!pixmap_.isNull()) {
            painter.drawPixmap((this->width() - pixmap_.width())/2, (this->height() - pixmap_.height())/2, pixmap_);
        }
    }

    void TcImageButton::enterEvent(QEnterEvent *event) {
        enter_ = true;
        repaint();
    }

    void TcImageButton::leaveEvent(QEvent *event) {
        enter_ = false;
        repaint();
    }

    void TcImageButton::mousePressEvent(QMouseEvent *event) {
        pressed_ = true;
        repaint();
    }

    void TcImageButton::mouseReleaseEvent(QMouseEvent *event) {
        pressed_ = false;
        repaint();
    }

}
//
// Created by RGAA on 19/03/2025.
//

#include "tc_image_button.h"
#include <QtSvg/QSvgRenderer>

namespace tc
{

    TcImageButton::TcImageButton(const QString& uri, const QSize& scale_size, QWidget* parent) : QWidget(parent) {
        img_uri_ = uri;
        scale_size_ = scale_size;
        if (!img_uri_.contains(".svg")) {
            pixmap_ = QPixmap::fromImage(QImage(uri));
            if (scale_size.width() > 0 && scale_size.height() > 0) {
                pixmap_ = pixmap_.scaled(scale_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }
        }
        else {
            renderer_.load(img_uri_);
        }
        setAttribute(Qt::WA_TranslucentBackground, true);

    }

    void TcImageButton::SetColor(int normal_color, int hover_color, int pressed_color) {
        this->normal_color_ = normal_color;
        this->hover_color_ = hover_color;
        this->pressed_color_ = pressed_color;
    }

    void TcImageButton::SetRoundRadius(int radius) {
        this->round_radius_ = radius;
    }

    void TcImageButton::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::VerticalSubpixelPositioning);
        painter.setRenderHint(QPainter::LosslessImageRendering);

        if (pressed_) {
            painter.setBrush(QBrush(pressed_color_));
        }
        else if (enter_) {
            painter.setBrush(QBrush(hover_color_));
        }
        else {
            if (normal_color_ != 0) {
                painter.setBrush(QBrush(normal_color_));
            }
            else {
                painter.setBrush(Qt::NoBrush);
            }
        }
        painter.drawRoundedRect(this->rect(), round_radius_, round_radius_);

        painter.setRenderHint(QPainter::Antialiasing, true);
        if (!pixmap_.isNull()) {
            painter.drawPixmap((this->width() - pixmap_.width())/2, (this->height() - pixmap_.height())/2, pixmap_);
        }

        if (scale_size_.width() <= 0) {
            renderer_.render(&painter, this->rect());
        }
        else {
            renderer_.render(&painter, QRect((this->width()-scale_size_.width())/2, (this->height()-scale_size_.height())/2, scale_size_.width(), scale_size_.height()));
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

        if (click_cbk_) {
            click_cbk_();
        }
    }

    void TcImageButton::SetOnImageButtonClicked(OnImageButtonClicked&& cbk) {
        click_cbk_ = cbk;
    }

}
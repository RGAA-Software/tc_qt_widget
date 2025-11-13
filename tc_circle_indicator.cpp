//
// Created by RGAA on 13/11/2025.
//

#include "tc_circle_indicator.h"

namespace tc
{

    TcCircleIndicator::TcCircleIndicator(QWidget* parent) : QWidget(parent) {

    }

    TcCircleIndicator::~TcCircleIndicator() {

    }

    void TcCircleIndicator::paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen(0x777777);
        painter.setPen(pen);
        painter.setBrush(QBrush(0x00ff00));
        painter.drawRoundedRect(1, 1, this->width()-2, this->height()-2, this->width()/2, this->height()/2);
    }

}
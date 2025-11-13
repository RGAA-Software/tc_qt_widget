//
// Created by RGAA on 13/11/2025.
//

#ifndef GAMMARAYPREMIUM_TC_CIRCLE_INDICATOR_H
#define GAMMARAYPREMIUM_TC_CIRCLE_INDICATOR_H

#include <QWidget>
#include <QPainter>

namespace tc
{

    class TcCircleIndicator : public QWidget {
    public:
        TcCircleIndicator(QWidget* parent = nullptr);
        ~TcCircleIndicator() override;

        void paintEvent(QPaintEvent *event) override;

    };

}

#endif //GAMMARAYPREMIUM_TC_CIRCLE_INDICATOR_H

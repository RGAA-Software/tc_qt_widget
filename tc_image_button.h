//
// Created by RGAA on 19/03/2025.
//

#ifndef GAMMARAY_TC_IMAGE_BUTTON_H
#define GAMMARAY_TC_IMAGE_BUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QtSvg/QSvgRenderer>
#include <functional>

namespace tc
{

    using OnImageButtonClicked = std::function<void()>;

    class TcImageButton : public QWidget {
    public:
        explicit TcImageButton(const QString& uri, const QSize& scale_size = QSize(0, 0), QWidget* parent = nullptr);
        void SetColor(int normal_color, int hover_color, int pressed_color);
        void SetRoundRadius(int radius);
        void SetOnImageButtonClicked(OnImageButtonClicked&& cbk);

        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEnterEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        QPixmap pixmap_;
        bool enter_ = false;
        bool pressed_ = false;
        int normal_color_ = 0;
        int hover_color_ = 0;
        int pressed_color_ = 0;
        int round_radius_ = 0;
        QString img_uri_;
        QSvgRenderer renderer_;
        OnImageButtonClicked click_cbk_;
        QSize scale_size_;
    };

}

#endif //GAMMARAY_TC_IMAGE_BUTTON_H

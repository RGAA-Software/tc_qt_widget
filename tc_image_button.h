//
// Created by RGAA on 19/03/2025.
//

#ifndef GAMMARAY_TC_IMAGE_BUTTON_H
#define GAMMARAY_TC_IMAGE_BUTTON_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

namespace tc
{

    class TcImageButton : public QWidget {
    public:
        explicit TcImageButton(const QString& uri, const QSize& scale_size = QSize(0, 0), QWidget* parent = nullptr);

        void paintEvent(QPaintEvent *event) override;
        void enterEvent(QEnterEvent *event) override;
        void leaveEvent(QEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private:
        QPixmap pixmap_;
        bool enter_ = false;
        bool pressed_ = false;
    };

}

#endif //GAMMARAY_TC_IMAGE_BUTTON_H

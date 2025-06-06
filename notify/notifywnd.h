﻿#ifndef NOTIFYWND_H
#define NOTIFYWND_H

#include "arrangedwnd.h"
#include <QLabel>
#include <QPushButton>

namespace tc
{

    class TcImageButton;

    class NotifyWnd : public ArrangedWnd {
    Q_OBJECT

    public:
        explicit NotifyWnd(NotifyManager *manager, QWidget *parent = 0);

        QVariantMap data() const;

        void setData(const QVariantMap &data);

    private:
        QVariantMap m_data;
        QFrame *background;
        QLabel *iconLabel;
        QLabel *titleLabel;
        QLabel *bodyLabel;
        TcImageButton *closeBtn;
    };

// 队列提示数
    class NotifyCountWnd : public ArrangedWnd {
    Q_OBJECT

    public:
        explicit NotifyCountWnd(NotifyManager *manager, QWidget *parent = 0);

        void setCount(int count);

    private:
        QLabel *iconLabel;
        QLabel *countLabel;
        QPropertyAnimation *flickerAnim;
    };

}

#endif // NOTIFYWND_H

﻿#ifndef WIN10HORIZONTALLOADINGWIDGET_H
#define WIN10HORIZONTALLOADINGWIDGET_H

#include "baseloadingwidget.h"

namespace tc
{

    class Win10HorizontalLoadingWidget : public BaseLoadingWidget {
    Q_OBJECT
    public:
        explicit Win10HorizontalLoadingWidget(QWidget *parent = nullptr);

        void setItemCount(const int &count); // 设置数量
        // 设置长度
        void setItemLength(const int &dotRadius) { m_itemLength = dotRadius; }

        void setItemColor(const int &index, const QColor &color); // 设置某个item的颜色
        void setItemColors(const QList<QColor> &colors); // 设置item的颜色
        void setBackgroundColor(const QColor &color) { m_bgColor = color; } // 设置背景颜色

    private slots:

        void animationStoped();

    protected:
        inline int currentFrame() { return m_currentFrame; }

        inline void setCurrentFrame(const int &frame) { m_currentFrame = frame; }

        inline QColor backgroundColor() { return m_bgColor; }

        inline QList<QColor> itemColors() { return m_itemColors; }

        inline int totalCount() { return m_totalCount; }

        inline void setTotalCount(const int &count) { m_totalCount = count; }

        inline int itemLength() { return m_itemLength; }

        inline int itemCount() { return m_itemCount; }

    protected:
        virtual void updateFrame() override;

        virtual void updateFrameRects() override;

        virtual void paintEvent(QPaintEvent *) override;

        virtual void resizeEvent(QResizeEvent *) override;

    private:
        int m_itemCount; // 运动对象数量
        int m_itemLength; // 运动对象
        int m_currentFrame; // 当前帧下标
        QColor m_bgColor; // 独立显示时的背景颜色
        QList<QColor> m_itemColors; // item的颜色
        int m_totalCount; // 总共的帧数
    };

}

#endif // WIN10HORIZONTALLOADINGWIDGET_H

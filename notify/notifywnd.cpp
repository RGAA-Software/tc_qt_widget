#include "notifywnd.h"
#include "notifymanager.h"
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>
#include "no_margin_layout.h"
#include "tc_qt_widget/tc_image_button.h"

namespace tc
{

    NotifyWnd::NotifyWnd(NotifyManager *manager, QWidget *parent)
            : ArrangedWnd(manager, parent) {
        background = new QFrame(this);
        background->setGeometry(3, 3, width() - 6, height() - 6);
        background->setObjectName("notify-background");

        QHBoxLayout *mainLayout = new NoMarginHLayout();
        QVBoxLayout *contentLayout = new NoMarginVLayout();

        auto icon_layout = new NoMarginVLayout();
        iconLabel = new QLabel(background);
        iconLabel->setFixedSize(40, 40);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setWordWrap(true);
        icon_layout->addStretch();
        icon_layout->addWidget(iconLabel);
        icon_layout->addStretch();

        titleLabel = new QLabel(background);
        titleLabel->setObjectName("notify-title");
        //titleLabel->setFont(sk::SysConfig::Instance()->sys_font_9);

        bodyLabel = new QLabel(background);
        bodyLabel->setObjectName("notify-body");
        //bodyLabel->setFont(sk::SysConfig::Instance()->sys_font_9);
        bodyLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        bodyLabel->setWordWrap(true);

        contentLayout->addSpacing(15);
        contentLayout->addWidget(titleLabel);
        contentLayout->addSpacing(6);
        contentLayout->addWidget(bodyLabel);
        contentLayout->addStretch();

        mainLayout->addSpacing(10);
        mainLayout->addLayout(icon_layout);
        mainLayout->addSpacing(12);
        mainLayout->addLayout(contentLayout);
        mainLayout->setAlignment(iconLabel, Qt::AlignTop);

        setLayout(mainLayout);

        closeBtn = new TcImageButton(":/resources/image/ic_close.svg", QSize(20, 20), background);
        closeBtn->SetColor(0xffffff, 0xdddddd, 0xaaaaaa);
        closeBtn->setObjectName("notify-close-btn");
        closeBtn->setFixedSize(28, 28);
        closeBtn->move(background->width() - closeBtn->width() - 5, 5);
        closeBtn->SetOnImageButtonClicked([=, this]() {
            this->deleteLater();
        });
        //connect(closeBtn, &QPushButton::clicked, this, &QObject::deleteLater);

        setStyleSheet(m_manager->styleSheet());

        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setOffset(0, 0);
        shadow->setBlurRadius(5);
        background->setGraphicsEffect(shadow);

        connect(this, &ArrangedWnd::visibleChanged, [this](bool visible) {
            if (visible) {
                int displayTime = m_data.value("displayTime", m_manager->displayTime()).toInt();
                QTimer::singleShot(displayTime, this, [this]() {
                    showArranged(0);
                });
            } else deleteLater();
        });
    }

    QVariantMap NotifyWnd::data() const {
        return m_data;
    }

// 需显示后调用
    void NotifyWnd::setData(const QVariantMap &data) {
        m_data = data;

        QPixmap icon;
        QVariant iconv = data.value("icon");
        if (iconv.type() == QVariant::Pixmap) icon = iconv.value<QPixmap>();
        if (iconv.type() == QVariant::String) icon = QPixmap(iconv.toString());
        else icon = QPixmap(m_manager->defaultIcon());

        if (data.contains("type") && data.value("type") == "err") {
            icon = QPixmap(m_manager->errorIcon());
        }

        icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        iconLabel->setPixmap(icon);

        QString title = data.value("title").toString();
        titleLabel->setText(title);

        // 计算可显示行数及长度
        QString body = m_data.value("body").toString();
        bodyLabel->setText(body);
#if 0
        QSize s1 = bodyLabel->size();
        QSize s2 = bodyLabel->fontMetrics().size(Qt::TextSingleLine, body);
        int linecount = s1.height()/s2.height();
        int charcount = qFloor(1.0*body.size()*s1.width()/s2.width()) * linecount;
        QString bodyElid = charcount > body.size() ? body : (body.left(charcount-1)+"...");
        bodyLabel->setText(bodyElid);
#endif
        if (data.contains("styleSheet"))
            setStyleSheet(data.value("styleSheet").toString());
        else if (data.contains("theme"))
            setStyleSheet(m_manager->styleSheet(data.value("theme").toString()));
    }

    NotifyCountWnd::NotifyCountWnd(NotifyManager *manager, QWidget *parent)
            : ArrangedWnd(manager, parent) {
        setAttribute(Qt::WA_TransparentForMouseEvents, true);

        iconLabel = new QLabel(this);
        iconLabel->setFixedSize(40, 40);
        iconLabel->setAlignment(Qt::AlignCenter);

        countLabel = new QLabel(this);
        countLabel->setObjectName("notify-count");
        countLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        QHBoxLayout *mainLayout = new QHBoxLayout(this);
        mainLayout->addWidget(iconLabel);
        mainLayout->addWidget(countLabel);

        // 文字阴影
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setOffset(2, 2);
        shadow->setBlurRadius(5);
        setGraphicsEffect(shadow);

        setStyleSheet("#notify-count {"
                      "font: 20px Verdana;"
                      "color: #dd424d;"
                      "}");

        QPixmap icon = QPixmap(m_manager->defaultIcon());
        icon = icon.scaled(QSize(32, 32), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        iconLabel->setPixmap(icon);

        flickerAnim = new QPropertyAnimation(this, "windowOpacity", this);
        flickerAnim->setStartValue(1);
        flickerAnim->setKeyValueAt(0.25, 0.1);
        flickerAnim->setKeyValueAt(0.5, 1);
        flickerAnim->setEndValue(1);
        flickerAnim->setDuration(2000);
        flickerAnim->setLoopCount(-1);

        connect(this, &ArrangedWnd::visibleChanged, [this](bool visible) {
            if (visible) flickerAnim->start();
            else flickerAnim->stop();
        });
    }

    void NotifyCountWnd::setCount(int count) {
        countLabel->setNum(count);
    }

}
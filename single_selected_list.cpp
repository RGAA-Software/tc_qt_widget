//
// Created by RGAA on 26/08/2024.
//

#include <QLabel>
#include "single_selected_list.h"
#include "clickable_widget.h"
#include "no_margin_layout.h"
#include "tc_common_new/log.h"

#include <QTimer>
#include <QStyledItemDelegate>

namespace tc
{

    // To fix the position of item
    class ItemDelegate : public QStyledItemDelegate {
    public:
        explicit ItemDelegate(QObject* parent) {}
        ~ItemDelegate() override = default;

        void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
            editor->setGeometry(option.rect);
        }
    };

    SingleSelectedList::SingleSelectedList(QWidget* parent) : QWidget(parent) {
        list_ = new QListWidget(this);
        list_->setItemDelegate(new ItemDelegate(this));
        list_->setSpacing(0);
        list_->setContentsMargins(0,0,0,0);
        list_->setResizeMode(QListView::ResizeMode::Fixed);
        list_->setMovement(QListView::Movement::Static);
        list_->setFlow(QListView::Flow::TopToBottom);
        list_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        //list_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        list_->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        list_->setStyleSheet("QListWidget {background: #ffffff;}"
                             "QListWidget::item:selected { background-color: transparent; }");

        connect(list_, &QListWidget::itemClicked, this, [=, this](QListWidgetItem *item) {
//            auto index = list_->indexFromItem(item);
//            Select(index.row());
        });

        auto layout = new NoMarginVLayout();
        layout->addWidget(list_);
        setLayout(layout);
    }

    QListWidgetItem* SingleSelectedList::AddItem(const SingleItemPtr& data, int index) {
        auto item = new QListWidgetItem(list_);
        item->setSizeHint(QSize(200, 38));
        auto widget = new ClickableWidget(list_);
        widget->setFixedSize(item->sizeHint());
        auto root_layout = new NoMarginHLayout();

        auto name = new QLabel(widget);
        name->setObjectName("name");
        name->setText(data->name_);
        name->setStyleSheet("padding-left: 10px;");
        root_layout->addWidget(name);

        auto icon_size = QSize(40, 40);
        auto icon = new QLabel(widget);
        icon->setObjectName("icon");
        icon->hide();
        icon->setFixedSize(icon_size);
        icon->setStyleSheet(R"( background-image: url(:resources/image/ic_check.svg);
                                    background-repeat:no-repeat;
                                    background-position: center center;)");
        select_indicators_.insert({index, icon});
        root_layout->addStretch();
        root_layout->addWidget(icon);
        root_layout->addSpacing(10);
        widget->setLayout(root_layout);
        list_->setItemWidget(item, widget);

        widget->SetOnClickListener([=, this](auto w) {
//            for (const auto[idx, ic] : select_indicators_) {
//                ic->hide();
//            }
//            icon->show();

            Select(index);
        });

        return item;
    }

    void SingleSelectedList::UpdateItems(const std::vector<SingleItemPtr> &items) {
        list_->setFixedWidth(this->width());
        items_ = items;
        int index = 0;
        for (const auto& item : items_) {
            AddItem(item, index++);
        }
        list_->update();
        list_->updateGeometry();
    }

    void SingleSelectedList::Select(int idx) const {
        if (idx < 0 || idx >= list_->count()) {
            return;
        }
        for (const auto[i, ic] : select_indicators_) {
            if (i == idx) {
                ic->show();
            } else {
                ic->hide();
            }
        }
    }

    std::vector<SingleItemPtr> SingleSelectedList::GetItems() {
        return items_;
    }
}
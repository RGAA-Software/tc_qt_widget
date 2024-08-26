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
        list_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        list_->setStyleSheet("QListWidget {background: #ffffff;}"
                             "QListWidget::item:selected { background-color: transparent; }");

        auto layout = new NoMarginVLayout();
        layout->addWidget(list_);
        setLayout(layout);
    }

    QListWidgetItem* SingleSelectedList::AddItem(const SingleItemPtr& data) {
        auto item = new QListWidgetItem(list_);
        item->setSizeHint(QSize(200, 38));
        auto widget = new ClickableWidget(this);
        widget->setFixedSize(item->sizeHint());
        auto root_layout = new NoMarginHLayout();

        auto name = new QLabel(this);
        name->setFixedSize(item->sizeHint());
        name->setObjectName("name");
        name->setText(data->name_);
        name->setStyleSheet("padding-left: 10px;");
        root_layout->addWidget(name);

        widget->setLayout(root_layout);
        list_->setItemWidget(item, widget);

        return item;
    }

    void SingleSelectedList::UpdateItems(const std::vector<SingleItemPtr> &items) {
        list_->setFixedWidth(this->width());
        items_ = items;
        for (const auto& item : items_) {
            AddItem(item);
        }
        list_->update();
        list_->updateGeometry();
    }

}
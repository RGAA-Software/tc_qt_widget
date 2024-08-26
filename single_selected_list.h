//
// Created by RGAA on 26/08/2024.
//

#ifndef GAMMARAYPC_SINGLE_SELECTED_LIST_H
#define GAMMARAYPC_SINGLE_SELECTED_LIST_H

#include <QListWidget>
#include <QString>

namespace tc
{

    //
    class SingleItem {
    public:
        QString name_;
        QString icon_path_;
        bool selected_{false};
    };
    using SingleItemPtr = std::shared_ptr<SingleItem>;

    //
    class SingleSelectedList :  public QWidget {
    public:
        explicit SingleSelectedList(QWidget* parent = nullptr);

        void UpdateItems(const std::vector<SingleItemPtr>& items);

    private:
        QListWidgetItem* AddItem(const SingleItemPtr& data);

    public:
        QListWidget* list_ = nullptr;
        std::vector<SingleItemPtr> items_;
    };

}

#endif //GAMMARAYPC_SINGLE_SELECTED_LIST_H

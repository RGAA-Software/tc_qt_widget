//
// Created by RGAA on 26/08/2024.
//

#ifndef GAMMARAYPC_CLICK_LISTENER_H
#define GAMMARAYPC_CLICK_LISTENER_H

#include <memory>
#include <functional>
#include <QWidget>

namespace tc
{

    using OnClickListener = std::function<void(QWidget*)>;
    using OnDoubleClickListener = std::function<void(QWidget*)>;
    using OnItemClickListener = std::function<void(int idx, QWidget*)>;

}

#endif //GAMMARAYPC_CLICK_LISTENER_H

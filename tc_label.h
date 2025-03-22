//
// Created by RGAA on 22/03/2025.
//

#ifndef GAMMARAY_TC_LABEL_H
#define GAMMARAY_TC_LABEL_H

#include <QLabel>

#include "translator/tc_translator.h"

namespace tc
{

    class TcLabel : public QLabel, public TcTranslator {
    public:
        explicit TcLabel(QWidget* parent = nullptr);
        ~TcLabel() override;

        void SetTextId(const QString& id) override;
        void OnTranslate(LanguageKind kind) override;
    };

}

#endif //GAMMARAY_TC_LABEL_H

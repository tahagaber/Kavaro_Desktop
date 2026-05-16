#include "SettingsCard.h"

SettingsCard::SettingsCard(const QString& title, QWidget* parent) : QFrame(parent) {
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    auto* card = new QFrame;
    card->setObjectName("SettingsCardFrame");
    card->setStyleSheet(R"(
        #SettingsCardFrame {
            background-color: #1e293b;
            border: 1px solid #334155;
            border-radius: 16px;
        }
        QLabel { background: transparent; border: none; padding: 0; }
        QFrame { background: transparent; border: none; }
    )");

    m_contentLayout = new QVBoxLayout(card);
    m_contentLayout->setContentsMargins(30, 30, 30, 30);
    m_contentLayout->setSpacing(25);
    
    mainLayout->addWidget(card);
}

void SettingsCard::setContent(QLayout* layout) {
    m_contentLayout->addLayout(layout);
}

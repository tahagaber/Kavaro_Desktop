#include "NotificationCard.h"

NotificationCard::NotificationCard(const NotificationData& data, QWidget* parent) 
    : QWidget(parent), m_data(data) {
    
    // Set fixed height or let it expand based on content
    setMinimumHeight(120);

    // Main Layout wrapper
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 15);

    auto* cardFrame = new QFrame(this);
    QString borderColor = getBorderColor();
    cardFrame->setStyleSheet(QString(R"(
        QFrame {
            background-color: #1a2235;
            border-radius: 8px;
            border-left: 4px solid %1;
        }
    )").arg(borderColor));

    mainLayout->addWidget(cardFrame);

    // Inside the card
    auto* cardLayout = new QHBoxLayout(cardFrame);
    cardLayout->setContentsMargins(20, 25, 20, 25);
    cardLayout->setSpacing(20);

    // 1. Icon
    auto* iconContainer = new QLabel;
    iconContainer->setFixedSize(40, 40);
    iconContainer->setAlignment(Qt::AlignCenter);
    
    QString iconStr = getIconStr();
    QString iconColor = getIconColor();
    QString iconBgStr = getIconColor(); // Background with alpha, we'll fake it with hex
    
    // Just lower opacity for bg
    QString fakeBgColor;
    if (m_data.type == NotificationType::Success) fakeBgColor = "#1a362f";
    else if (m_data.type == NotificationType::Info) fakeBgColor = "#182a4d";
    else fakeBgColor = "#3a2128";

    iconContainer->setText(iconStr);
    iconContainer->setStyleSheet(QString(R"(
        QLabel {
            background-color: %1;
            color: %2;
            border-radius: 20px;
            font-size: 16px;
            font-weight: bold;
        }
    )").arg(fakeBgColor, iconColor));
    cardLayout->addWidget(iconContainer, 0, Qt::AlignTop);

    // 2. Body
    auto* bodyLayout = new QVBoxLayout;
    bodyLayout->setSpacing(8);

    // Top row of body (Title + Time)
    auto* topRowLayout = new QHBoxLayout;
    auto* titleLabel = new QLabel(data.title);
    titleLabel->setStyleSheet(R"(
        QLabel {
            color: #f8fafc;
            font-size: 16px;
            font-weight: bold;
            background: transparent;
            border: none;
        }
    )");
    auto* timeLabel = new QLabel(data.timeAgo);
    timeLabel->setStyleSheet(R"(
        QLabel {
            color: #64748b;
            font-size: 11px;
            font-weight: bold;
            letter-spacing: 1px;
            background: transparent;
            border: none;
        }
    )");
    topRowLayout->addWidget(titleLabel);
    topRowLayout->addStretch();
    topRowLayout->addWidget(timeLabel);

    bodyLayout->addLayout(topRowLayout);

    // Description
    auto* descLabel = new QLabel(data.description);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet(R"(
        QLabel {
            color: #94a3b8;
            font-size: 13px;
            background: transparent;
            border: none;
        }
    )");
    bodyLayout->addWidget(descLabel);

    // Tags list
    auto* tagsLayout = new QHBoxLayout;
    tagsLayout->setSpacing(10);
    tagsLayout->setAlignment(Qt::AlignLeft);

    auto* primaryTag = new QLabel(data.primaryTag.toUpper());
    primaryTag->setStyleSheet(QString(R"(
        QLabel {
            color: %1;
            background-color: %2;
            padding: 4px 8px;
            border-radius: 4px;
            font-size: 10px;
            font-weight: bold;
            letter-spacing: 1px;
            border: none;
        }
    )").arg(iconColor, fakeBgColor));
    tagsLayout->addWidget(primaryTag);

    if (!data.secondaryTag.isEmpty()) {
        auto* secondaryTag = new QLabel(data.secondaryTag.toUpper());
        secondaryTag->setStyleSheet(R"(
            QLabel {
                color: #64748b;
                font-size: 11px;
                letter-spacing: 1px;
                background: transparent;
                border: none;
            }
        )");
        tagsLayout->addWidget(secondaryTag);
    }
    tagsLayout->addStretch();

    bodyLayout->addLayout(tagsLayout);

    cardLayout->addLayout(bodyLayout);
}

QString NotificationCard::getBorderColor() const {
    switch (m_data.type) {
        case NotificationType::Success: return "#10b981"; // Green
        case NotificationType::Info:    return "#3b82f6"; // Blue
        case NotificationType::Error:   return "#ef4444"; // Red
    }
    return "#cbd5e1";
}

QString NotificationCard::getIconColor() const {
    return getBorderColor();
}

QString NotificationCard::getIconStr() const {
    switch (m_data.type) {
        case NotificationType::Success: return "✔️";
        case NotificationType::Info:    return "$";
        case NotificationType::Error:   return "!";
    }
    return "i";
}
